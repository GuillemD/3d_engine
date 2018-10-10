#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void Focus(AABB& box);
	float* GetViewMatrix();

	void ShowCameraConfiguration();

private:

	void CalculateViewMatrix();
	mat4x4 ViewMatrix, ViewMatrixInverse;
public:

	vec3 X, Y, Z, Position, Reference;
	float Sensitivity;
	bool can_focus = false;

};