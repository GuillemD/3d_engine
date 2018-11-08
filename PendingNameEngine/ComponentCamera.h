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
public:
	Frustum camerafrustum;
	AABB cameraboundingbox;
};





#endif // !_Component_Camera_



