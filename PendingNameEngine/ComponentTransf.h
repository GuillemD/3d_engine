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
	void SetPosition(float _x, float _y, float _z);
	float3 GetPosition() const;

	void SetScale(float3 _sca);
	void SetScale(float _x, float _y, float _z);
	float3 GetScale() const;

	void SetRotation(Quat _rot);
	void SetRotation(const float3& _rot);
	Quat GetRotation() const;
	float3 GetEulerRotation() const;

	void SetTransform(float3 _pos, float3 _scale, Quat _rot);
	void SetGlobalTransf(const float4x4& g_transf);
	float4x4 GetGlobalTransf() const;

	void RecalculateTransform();
	void ChangeTransformEvent();

	void DrawInInspector();

public:
	float3 position = { 0.0f,0.0f,0.0f };
	float3 scal = { 1.0f,1.0f,1.0f };
	float3 eulerRotation = { 0.0f,0.0f,0.0f };
	Quat quatRotation = { 1.0f,0.0f,0.0f,0.0f };

	float4x4 globalTransf;

};

#endif // ! __COMPONENT_TRANSFORM_H__
