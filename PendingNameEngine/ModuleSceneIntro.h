#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

struct PhysBody3D;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void DrawGrid(int HALF_GRID_SIZE);
	

	PPlane pl=PPlane(1.0f,1.0f,1.0f,1.0f);
public:
	bool grid_active = true;

};
