#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "SDL/include/SDL_opengl.h"


ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	if (App->renderer3D->show_plane == true)
	{
		PPlane base_plane(0, 1, 0, 0);
		base_plane.axis = true;
		base_plane.Render();
	}

	App->camera->Move(float3(1.0f, 10.0f, 0.0f));
	App->camera->LookAt(float3(0.0f, 0.0f, 0.0f));
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
update_status ModuleSceneIntro::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}




