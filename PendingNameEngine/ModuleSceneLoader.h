#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "Mesh.h"

#include <list>

class ModuleSceneLoader : public Module
{
public:
	ModuleSceneLoader(bool start_enabled = true);
	~ModuleSceneLoader();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Draw() ;

public:
	std::list<Mesh*> scene_objects;

	bool first_mesh = true;

private:
	Mesh cube;


};
