#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include <list>
#include "MathGeoLib/MathGeoLib.h"


// Recommended scale is 1.0f == 1 meter, no less than 0.2 objects
#define GRAVITY vec(0.0f, -10.0f, 0.0f) 

class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void CreateSphere(vec position, float radius);
	void CreateCylinder(vec position, float radius, float height);
	void CreateCapsule(float radius, LineSegment l);
	void CreateCube(vec aabbmin, vec aabbmax);

	std::list<float2> GetSphereCollisionsList();
	std::list<float2> GetCubeCollisionsList();



	std::vector<math::Sphere> SpheresArray;
	std::vector<math::Capsule> CapsulesArray;
	std::vector<math::AABB> CubesArray;

	
private:
	

public:
	bool debug;
};

