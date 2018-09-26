#pragma once
#include "Module.h"
#include "Globals.h"


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
	
public:
	bool grid_active = true;

};
