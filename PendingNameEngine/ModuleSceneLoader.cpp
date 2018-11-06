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

	
	App->importer->Import(".//Assets//BakerHouse.fbx");
	ComponentMaterial* baker_text = App->texture->LoadTexFromPath(".//Assets//Baker_House.png");
	scene_objects[0]->AddComponent((Component*)baker_text);
	
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
void ModuleSceneLoader::DrawSceneGO()
{
	for (uint i = 0; i < scene_objects.size(); i++)
	{
		if(scene_objects[i]->IsActive())
			scene_objects[i]->Draw();
	}

}

void ModuleSceneLoader::DrawHierarchy()
{
	std::vector<GameObject*> root_obj;
	for (uint i = 0; i < scene_objects.size(); i++)
	{
		if (scene_objects[i]->parent == nullptr)
		{
			root_obj.push_back(scene_objects[i]);
		}
	}
	for (uint j = 0; j < root_obj.size(); j++)
	{
		if (bool draw = ImGui::TreeNode(root_obj[j]->name.c_str()))
		{
			root_obj[j]->DrawInHierarchy();
		}

	}
}

GameObject * ModuleSceneLoader::CreateGameObject(std::string go_name)
{
	
	GameObject* created_go = new GameObject(go_name);
	scene_objects.push_back(created_go);
	
	return created_go;
}

update_status ModuleSceneLoader::Update(float dt)
{
	return UPDATE_CONTINUE;
}




