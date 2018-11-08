#ifndef _Component_Camera_
#define _Component_Camera_

#include "Component.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Globals.h"
#include "GLEW/include/glew.h"

class ComponentCamera : public Component {
public:
	ComponentCamera();
	~ComponentCamera();

	void SetAspectRatio(float _aspectratio);
	void DrawCameraBoundingBox();


	float GetNearPlaneDist() const;
	float GetFarPlaneDist() const;
	float GetFOV() const;
	float GetAspectRatio() const;

	void SetNearPlaneDist(float dist);
	void SetFarPlaneDist(float dist);
	void SetFOV(float fov);
	
	void Look(const float3& position);

	float* GetOpenGLViewMatrix();
	float* GetOpenGLProjectionMatrix();

public:
	Frustum camerafrustum;
	AABB cameraboundingbox;
};





#endif // !_Component_Camera_



