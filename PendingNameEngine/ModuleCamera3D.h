#pragma once
#include "Module.h"
#include "Globals.h"


class btRigidBody;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec &Position, const vec &Reference, bool RotateAroundReference = false);
	void LookAt(const vec &Spot);
	void Move(const vec &Movement);
	float* GetViewMatrix();

private:
	float maxDistanceToVehicle = 25.0f;
	void CalculateViewMatrix();
	float4x4 ViewMatrix, ViewMatrixInverse;
	bool isPlaying = false;
public:
	
	vec X, Y, Z, Position, Reference;
	
};