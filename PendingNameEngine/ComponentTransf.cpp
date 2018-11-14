#include "ComponentTransf.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

#include <vector>

ComponentTransf::ComponentTransf(GameObject* _gameobject)
{
	if (_gameobject != nullptr) {
		MyType = TRANSFORMATION;
		my_go = _gameobject;
		name = "Component Transformation";
	}

	globalTransf = float4x4::FromTRS(position, quatRotation, scal);
}

ComponentTransf::~ComponentTransf()
{
}

void ComponentTransf::SetPosition(float3 _pos)
{
	position = _pos;

	RecalculateTransform();
}

void ComponentTransf::SetPosition(float _x, float _y, float _z)
{
	position.x = _x; position.y = _y; position.z = _z;

	RecalculateTransform();
}

float3 ComponentTransf::GetPosition() const
{
	return position;
}

void ComponentTransf::SetScale(float3 _sca)
{
	scal = _sca;

	RecalculateTransform();
}

void ComponentTransf::SetScale(float _x, float _y, float _z)
{
	scal.x = _x; scal.y = _y; scal.z = _z;

	RecalculateTransform();
}

float3 ComponentTransf::GetScale() const
{
	return scal;
}

void ComponentTransf::SetRotation(Quat _rot)
{
	quatRotation = _rot;
	RecalculateTransform();
}

void ComponentTransf::SetRotation(const float3 & _rot)
{
	Quat aux = Quat::FromEulerXYZ(_rot.x, _rot.y, _rot.z);
	quatRotation = aux;
	eulerRotation = _rot;
}

Quat ComponentTransf::GetRotation() const
{
	return quatRotation;
}

float3 ComponentTransf::GetEulerRotation() const
{
	return eulerRotation;
}

void ComponentTransf::SetTransform(float3 _pos, float3 _scale, Quat _rot)
{
	position = _pos;
	scal = _scale;
	quatRotation = _rot;

	RecalculateTransform();

}

void ComponentTransf::SetGlobalTransf(const float4x4 & g_transf)
{
	globalTransf.Set(g_transf);
}

float4x4 ComponentTransf::GetGlobalTransf() const
{
	return globalTransf;
}

void ComponentTransf::RecalculateTransform()
{
	if (GetOwner()->GetParent() == nullptr) {
		globalTransf = float4x4::FromTRS(position, quatRotation, scal);
		
	}
		
	else
	{
		ComponentTransf* parent = (ComponentTransf*)GetOwner()->GetParent()->GetComponentByType(TRANSFORMATION);
		globalTransf = parent->GetGlobalTransf()*float4x4::FromTRS(position, quatRotation, scal);
		
	}
	
	GetOwner()->OnTransformEvent();
	
}

void ComponentTransf::ChangeTransformEvent()
{
	if (GetOwner()->GetParent() == nullptr)
		globalTransf = float4x4::FromTRS(position, quatRotation, scal);
	else
	{
		ComponentTransf* parent = (ComponentTransf*)GetOwner()->GetParent()->GetComponentByType(TRANSFORMATION);
		globalTransf = parent->globalTransf*float4x4::FromTRS(position, quatRotation, scal);
	}
}

void ComponentTransf::DrawInInspector()
{
	if (ImGui::CollapsingHeader("Component Transformation"))
	{
		float3 pos = { position.x, position.y, position.z };
		float3 rot = { RadToDeg(quatRotation.ToEulerXYZ().x), RadToDeg(quatRotation.ToEulerXYZ().y), RadToDeg(quatRotation.ToEulerXYZ().z) };
		float3 sc = { scal.x,scal.y,scal.z };

		bool call_update = false;
		if (!GetOwner()->IsStatic())
		{
			if (ImGui::DragFloat3("Position", (float*)&pos, 0.25f, -INFINITY, INFINITY))
			{
				position = { pos.x,pos.y,pos.z };
				call_update = true;
			}


			if (ImGui::DragFloat3("Rotation", (float*)&rot, 0.15f, -360, 360))
			{
				Quat new_rot = Quat::FromEulerXYZ(DegToRad(rot.x), DegToRad(rot.y), DegToRad(rot.z));
				call_update = true;
			}


			if (ImGui::DragFloat3("Scale", (float*)&sc, 0.05f, 0, INFINITY))
			{
				scal = { sc.x,sc.y,sc.z };
				call_update = true;

			}

			if (call_update)
				RecalculateTransform();
		}
		
	}
		

}
