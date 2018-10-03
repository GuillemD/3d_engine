#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "Mesh.h"

#include <list>
struct PhysBody3D;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Draw() ;

public:
	std::list<Mesh*> scene_objects;

private:
	Mesh cube;

};
