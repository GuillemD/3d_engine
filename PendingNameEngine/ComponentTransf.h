#ifndef __COMPONENT_TRANSFORM_H__
#define  __COMPONENT_TRANSFORM_H__

#include "Component.h"
#include "glmath.h"
#include "MathGeoLib/MathGeoLib.h"



class ComponentTransf : public Component {

public:
	ComponentTransf(GameObject* _gameobject);
	virtual ~ComponentTransf();

	void SetPosition(float3 _pos);
	float3 GetPosition() const;

	void SetScale(float3 _sca);
	float3 GetScale() const;

	void SetRotation(Quat _rot);
	void SetRotation(const float3& _rot);
	Quat GetRotation() const;
	float3 GetEulerRotation() const;

	void SetLocalTransf(const float4x4& l_transf);
	float4x4 GetLocalTransf() const;

	void SetGlobalTransf(const float4x4& g_transf);
	float4x4 GetGlobalTransf();

	void RecalculateTransform();

	void DrawInInspector();

private:
	float3 position = { 0.0f,0.0f,0.0f };
	float3 scale = { 1.0f,1.0f,1.0f };
	float3 eulerRotation = { 0.0f,0.0f,0.0f };
	Quat quatRotation = { 1.0f,0.0f,0.0f,0.0f };

	float4x4 localTransf;
	float4x4 globalTransf;

};

#endif // ! __COMPONENT_TRANSFORM_H__
