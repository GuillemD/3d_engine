#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"



ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = false;
	
	
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	
}

// Render not available yet----------------------------------
bool ModulePhysics3D::Init()
{
	LOG("Creating 3D Physics simulation");
	bool ret = true;

	return ret;
}

// ---------------------------------------------------------
bool ModulePhysics3D::Start()
{
	LOG("Creating Physics environment");

	

	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;


	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	LOG("Destroying 3D Physics simulation");
	// Remove from the world all collision bodies
	
	return true;
}

void ModulePhysics3D::CreateSphere(vec position, float radius)
{
	math::Sphere ret;
	ret.pos = position;
	ret.r = radius;
	SpheresArray.push_back(ret);
	LOG("Created sphere with radius %f",radius);
	
}

void ModulePhysics3D::CreateCylinder(vec position, float radius, float height)
{

	
}

void ModulePhysics3D::CreateCapsule(float radius, LineSegment l)
{
	math::Capsule ret;
	ret.r = radius;
	ret.l = l;
	CapsulesArray.push_back(ret);
	LOG("Created Capsule");
}

void ModulePhysics3D::CreateCube(vec aabbmin, vec aabbmax)
{
	math::AABB ret;
	ret.minPoint = aabbmin;
	ret.maxPoint = aabbmax;
	CubesArray.push_back(ret);
	LOG("Created cube");

}

std::list<float2> ModulePhysics3D::GetSphereCollisionsList()
{
	std::list<float2> SphereCollisionsList;
	int object_one = 0, object_two = 0;
	//To check if two objects of the same kind are colliding we use math::Wahtever.Intersects(). 
	//We use 2 fors to iterate and check all the items in the Sphere vector. Objects collisions with themselves should be ignored
	
	for (object_one; object_one < SpheresArray.size(); object_one++)
	{
		for (object_two; object_two < SpheresArray.size(); object_two++) {
			if (object_one == object_two) {
				continue;
			}
			if (SpheresArray[object_one].Intersects(SpheresArray[object_two])) {
				SphereCollisionsList.push_back({ (float)object_one, (float)object_two });
				LOG("Object %d intersects with Object %d", object_one, object_two);
			}
		}
		object_two = 0;
	}
	if (SphereCollisionsList.size() == 0) {
		LOG("There are no Spheres colliding with each other.")
	}
	return SphereCollisionsList;
}

std::list<float2> ModulePhysics3D::GetCubeCollisionsList()
{
	std::list<float2> CubeCollisionsList;
	int object_one= 0, object_two = 0;
	//To check if two objects of the same kind are colliding we use math::Wahtever.Intersects(). 
	//We use 2 fors to iterate and check all the items in the Sphere vector. Objects collisions with themselves should be ignored

	for (object_one; object_one < CubesArray.size(); object_one++)
	{
		for (object_two; object_two < CubesArray.size(); object_two++) {
			if (object_one == object_two) {
				continue;
			}
			if (CubesArray[object_one].Intersects(CubesArray[object_two])) {
				CubeCollisionsList.push_back({ (float)object_one, (float)object_two });
				LOG("Object %d intersects with Object %d", object_one, object_two);
			}
		}
		object_two = 0;
	}
	if (CubeCollisionsList.size() == 0) {
		LOG("There are no Cubes colliding with each other.")
	}
	return CubeCollisionsList;
}

std::list<float2> ModulePhysics3D::GetCapsuleCollisionsList()
{
	std::list<float2> CapsuleCollisionsList;
	int object_one = 0, object_two = 0;
	//To check if two objects of the same kind are colliding we use math::Wahtever.Intersects(). 
	//We use 2 fors to iterate and check all the items in the Sphere vector. Objects collisions with themselves should be ignored

	for (object_one; object_one < CapsulesArray.size(); object_one++)
	{
		for (object_two; object_two < CapsulesArray.size(); object_two++) {
			if (object_one == object_two) {
				continue;
			}
			if (CapsulesArray[object_one].Intersects(CapsulesArray[object_two])) {
				CapsuleCollisionsList.push_back({ (float)object_one, (float)object_two });
				LOG("Object %d intersects with Object %d.", object_one, object_two);
			}
		}
		object_two = 0;
	}
	if (CapsuleCollisionsList.size() == 0) {
		LOG("There are no Capsules colliding with each other.")
	}
	return CapsuleCollisionsList;
}

// ---------------------------------------------------------
