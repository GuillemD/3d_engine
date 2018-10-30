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

	void DrawSceneGO() ;
	//Create GO
	GameObject* CreateGameObject(std::string _name);

public:
	std::vector<GameObject*> scene_objects;

};
