#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLoader.h"
#include "Component.h"
#include "GameObject.h"
#include "ComponentMaterial.h"


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

	
	App->importer->Import(".//Assets//test2.fbx");
	
	
	GlobalQuadTree = new Quadtree(AABB(vec(-30, -20, -30), vec(10, 20, 10)), 0);

	
	


	App->camera->Move(vec3(0.0f, 10.0f, 10.0f));
	App->camera->LookAt(vec3(0.0f, 3.0f, 0.0f));

	App->renderer3D->OnResize(App->window->width, App->window->height);

	for (uint i = 0; i < scene_objects.size(); i++)
	{
		scene_objects[i]->staticgo = true;
	}


	for (uint i = 0; i < scene_objects.size(); i++)
	{
		if (scene_objects[i]->IsActive())
			GlobalQuadTree->Insert(scene_objects[i]);

	}

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
		uint flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (bool draw = ImGui::TreeNodeEx(root_obj[j]->name.c_str(), flags))
		{
			root_obj[j]->DrawInHierarchy();
			ImGui::TreePop();
		}

	}
}

void ModuleSceneLoader::DrawGOBoundingBoxes()
{
	for (uint i = 0; i < scene_objects.size(); i++)
	{
		if (scene_objects[i]->IsActive())
			scene_objects[i]->RenderBoundingBox();


	}

}

GameObject * ModuleSceneLoader::CreateGameObject(std::string go_name)
{
	
	GameObject* created_go = new GameObject(go_name);
	scene_objects.push_back(created_go);
	
	return created_go;
}

GameObject * ModuleSceneLoader::GetRoot() const
{

	return root;
}

update_status ModuleSceneLoader::Update(float dt)
{


	return UPDATE_CONTINUE;
}




