#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

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
	App->camera->Move(vec(0.0f, 10.0f, 0.0f));
	App->camera->LookAt(vec(0.0f, 0.0f, 0.0f));
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
update_status ModuleSceneIntro::Update(float dt)
{
	if (grid_active)
		DrawGrid(30);
	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::DrawGrid(int HALF_GRID_SIZE)
{
	
	
}



