#ifndef _MODULESCENELOADER_H_
#define _MODULESCENELOADER_H_
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

	void DrawSceneGO();
	void DrawHierarchy();

	//Create GO
	GameObject* CreateGameObject(std::string _name);

public:
	std::vector<GameObject*> scene_objects;

};
#endif // !_MODULESCENELOADER_H_


