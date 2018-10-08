#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

#include "OpenGL.h"


ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//cube.DefineVerticesAndIndicesForACube(vec(0.f, 0.f, 0.f), 1);
	//scene_objects.push_back(&cube);
	
	App->camera->Move(vec3(0.0f, 10.0f, 10.0f));
	App->camera->LookAt(vec3(0.0f, 3.0f, 0.0f));
	
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
void ModuleSceneIntro::Draw() 
{
	for (std::list<Mesh*>::iterator it = scene_objects.begin(); it != scene_objects.end(); it++)
	{
		(*it)->DrawMesh();
	}

}

update_status ModuleSceneIntro::Update(float dt)
{
	Draw();
	return UPDATE_CONTINUE;
}




