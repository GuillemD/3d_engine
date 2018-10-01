#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "Mesh.h"
struct PhysBody3D;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Draw() const;
public:
	Mesh VertexAndIndexCube;
	Mesh VertexArrayCube;
};
