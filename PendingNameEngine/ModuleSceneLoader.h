#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "Mesh.h"

#include <vector>

class GameObject;

class ModuleSceneLoader : public Module
{
public:
	ModuleSceneLoader(bool start_enabled = true);
	~ModuleSceneLoader();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Draw() ;
	//Create GO
	GameObject* CreateGameObject(GameObject* parent, std::string _name);
	//Tools
	GameObject* GetRoot() const;

public:
	std::vector<GameObject*> scene_objects;
	//bool first_mesh = true;
public:
	GameObject* root_go = nullptr;

};
