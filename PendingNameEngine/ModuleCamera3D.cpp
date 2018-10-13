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

	Sensitivity = 0.40f;
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

	if (ImGui::IsMouseHoveringAnyWindow())
		return UPDATE_CONTINUE;

	vec3 newPos(0, 0, 0);
	float speed = 20.0f * dt;
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
		can_focus = true;
	}

	if (App->input->GetMouseZ() > 0)
	{
		newPos -= Z * speed; //ZOOM IN

		can_focus = true;
		Position += newPos;
		Reference += newPos;

	}
	if (App->input->GetMouseZ() < 0) {
		newPos += Z * speed; can_focus = true;//ZOOM OUT
		Position += newPos;
		Reference += newPos;

	}

	
	// Mouse motion ----------------

	if ((App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT))) //orbit around center
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

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
		LookAt({ 0,0,0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		if (App->scene_loader->scene_objects.empty())
		{
			Position.x = 0.0f; Position.y = 10.0f; Position.z = 10.0f;
			LookAt(vec3(0.0f, 3.0f, 0.0f));
		}
		else
		{
			if(can_focus)
			{
				Focus(App->scene_loader->scene_objects.front()->outside_box);
			}
			
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

void ModuleCamera3D::Focus(AABB& box)
{
	
	/*Sphere tmp = box_focus.MinimalEnclosingSphere();
	float radius = tmp.r;
	float fov = DegToRad(60);
	float camDistance = (radius * 2.0) / Tan(fov / 2.0);
	Position = vec3(target - Position) * camDistance;*/
	if (can_focus)
	{
		float3 cam_pos = box.CenterPoint();
		vec3 target = { cam_pos.x, cam_pos.y, cam_pos.z }; //convert to be able to LookAt


		cam_pos.x += box.Diagonal().Length() + box.HalfDiagonal().Length();
		cam_pos.z -= box.Diagonal().Length() + box.HalfDiagonal().Length();
		cam_pos.y += box.Diagonal().Length() + box.HalfDiagonal().Length();


		Position.x = cam_pos.x;
		Position.y = cam_pos.y;
		Position.z = cam_pos.z;

		LookAt({ 0.f,0.f,0.f });
		can_focus = false;
	}
	
	CalculateViewMatrix();

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
