#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

	Sensitivity = 0.25f;
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{

		vec3 newPos(0, 0, 0);
		float speed = 15.0f * dt;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed = 60.0f * dt;

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) newPos.y += speed; //UP
			if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y -= speed; //DOWN

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed; //FORWARD
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed; //BACKWARD

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed; //LEFT
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed; //RIGHT


			Position += newPos;
			Reference += newPos;
		}

		if (App->input->GetMouseZ() > 0) newPos -= Z * speed; //ZOOM IN
		if (App->input->GetMouseZ() < 0) newPos += Z * speed; //ZOOM OUT

		Position += newPos;
		Reference += newPos;

		// Mouse motion ----------------

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT || (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT)))
		{
			float dx = -(float)App->input->GetMouseXMotion() *  dt;
			float dy = -(float)App->input->GetMouseYMotion() *  dt;			

			Position -= Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				Y = rotate(Y, DeltaY, X);
				Z = rotate(Z, DeltaY, X);

				if (Y.y < 0.0f)
				{
					Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Y = cross(Z, X);
				}
			}

			Position = Reference + Z * length(Position);
		}
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
		{
			if (App->scene_intro->scene_objects.empty())
			{
				Position.x = 0.0f; Position.y = 10.0f; Position.z = 10.0f;
				LookAt(vec3(0.0f, 3.0f, 0.0f));
			}
			else
			{
				Focus(App->scene_intro->scene_objects.front()->outside_box);
			}
		}

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

void ModuleCamera3D::Focus(AABB & box)
{
	AABB box_focus(float3::zero, float3::zero);

	if (box.minPoint.x < box_focus.minPoint.x) box_focus.minPoint.x = box.minPoint.x;
	if (box.minPoint.y < box_focus.minPoint.y) box_focus.minPoint.y = box.minPoint.y;
	if (box.minPoint.z < box_focus.minPoint.z) box_focus.minPoint.z = box.minPoint.z;
	if (box.maxPoint.x > box_focus.maxPoint.x) box_focus.maxPoint.x = box.maxPoint.x;
	if (box.maxPoint.y > box_focus.maxPoint.y) box_focus.maxPoint.y = box.maxPoint.y;
	if (box.maxPoint.z > box_focus.maxPoint.z) box_focus.maxPoint.z = box.maxPoint.z;

	float3 center = box_focus.CenterPoint();
	vec3 target = { center.x, center.y, center.z }; //convert to be able to LookAt

	//float radius = Distance(box_focus.minPoint.x, center.x);
	Sphere tmp = box_focus.MinimalEnclosingSphere();
	float radius = tmp.r;

	float fov = DegToRad(60);

	float camDistance = (radius * 2.0) / Tan(fov / 2.0);
	
	Position = vec3(target - Position) * camDistance;

	LookAt(target);

}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

void ModuleCamera3D::ShowCameraConfiguration()
{
	ImGui::Text("Camera x: %f", Position.x);
	ImGui::Text("Camera y: %f", Position.y);
	ImGui::Text("Camera z: %f", Position.z);

}
