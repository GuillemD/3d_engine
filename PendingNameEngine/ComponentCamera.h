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
	void DrawCameraFrustum();

	float GetNearPlaneDist() const;
	float GetFarPlaneDist() const;
	float GetFOV() const;
	float GetAspectRatio() const;

	void SetNearPlaneDist(float _dist);
	void SetFarPlaneDist(float _dist);
	void SetFOV(float _fov);
	
	void Look(const float3& _position);

	float* GetOpenGLViewMatrix();
	float* GetOpenGLProjectionMatrix();

	void AttachToGo(GameObject* _go);
public:
	Frustum camerafrustum;
	AABB cameraboundingbox;
};





#endif // !_Component_Camera_



