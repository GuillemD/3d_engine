#ifndef __COMPONENT_TRANSFORM_H__
#define  __COMPONENT_TRANSFORM_H__

#include "Component.h"
#include "MathGeoLib/MathGeoLib.h"


class ComponentTransf : public Component {

public:
	ComponentTransf(GameObject* _gameobject);
	~ComponentTransf();

private:
	float3 position = { 0.0f,0.0f,0.0f };
	float3 scale = { 1.0f,1.0f,1.0f };
	float3 eulerRotation = { 0.0f,0.0f,0.0f };
	Quat quatRotation = { 1.0f,0.0f,0.0f,0.0f };


};

#endif // ! __COMPONENT_TRANSFORM_H__
