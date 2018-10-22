#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLoader.h"
#include "Component.h"
#include "GameObject.h"

#include "OpenGL.h"


ModuleSceneLoader::ModuleSceneLoader(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneLoader::~ModuleSceneLoader()
{}

bool ModuleSceneLoader::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	/*App->texture->current = ".//Assets//Baker_House.png";
	App->texture->LoadTexFromPath(".//Assets//Baker_House.png");
	App->importer->Import(".//Assets//BakerHouse.fbx");*/

	root_go = new GameObject(nullptr, "root");
	
	App->camera->Move(vec3(0.0f, 10.0f, 10.0f));
	App->camera->LookAt(vec3(0.0f, 3.0f, 0.0f));

	App->renderer3D->OnResize(App->window->width, App->window->height);

	return ret; 
}

bool ModuleSceneLoader::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
void ModuleSceneLoader::Draw()
{
	/*for (std::list<Mesh*>::iterator it = scene_objects.begin(); it != scene_objects.end(); it++)
	{
		(*it)->DrawMesh();
	}*/

}

GameObject * ModuleSceneLoader::CreateGameObject(GameObject * parent, std::string go_name)
{
	if (parent == nullptr)
	{
		parent = root_go;
	}

	GameObject* created_go = new GameObject(parent, go_name);
	
	return created_go;
}


GameObject * ModuleSceneLoader::GetRoot() const
{
	return root_go;
}

update_status ModuleSceneLoader::Update(float dt)
{
	return UPDATE_CONTINUE;
}




