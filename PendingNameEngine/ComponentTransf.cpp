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
	scale = _sca;

	RecalculateTransform();
}

void ComponentTransf::SetScale(float _x, float _y, float _z)
{
	scale.x = _x; scale.y = _y; scale.z = _z;

	RecalculateTransform();
}

float3 ComponentTransf::GetScale() const
{
	return scale;
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
	scale = _scale;
	quatRotation = _rot;

	RecalculateTransform();

}

void ComponentTransf::SetLocalTransf(const float4x4 & l_transf)
{
	localTransf.Set(l_transf);
}

float4x4 ComponentTransf::GetLocalTransf() const
{
	return localTransf;
}

void ComponentTransf::SetGlobalTransf(const float4x4 & g_transf)
{
	globalTransf.Set(g_transf);
}

float4x4 ComponentTransf::GetGlobalTransf()
{
	globalTransf = globalTransf.FromTRS(position, quatRotation, scale);
	return globalTransf;
}

void ComponentTransf::RecalculateTransform()
{
	localTransf.Set(float4x4::FromTRS(position, quatRotation, scale));
	float4x4 global_to_replace(globalTransf);

	if (my_go->GetParent() != nullptr) {
		ComponentTransf* owner_transf = (ComponentTransf*)my_go->GetParent()->GetComponentByType(TRANSFORMATION);
		if (my_go != nullptr)
			globalTransf.Set(owner_transf->GetGlobalTransf().Mul(localTransf));
		else
			globalTransf.Set(localTransf);
	}
	else
		globalTransf.Set(localTransf);

	std::vector<GameObject*> iterate = my_go->GetChildren();
	ComponentTransf* child_transf;
	for (int i = 0; i < iterate.size(); ++i)
	{
		child_transf = (ComponentTransf*)iterate[i]->GetComponentByType(TRANSFORMATION);
		if (child_transf != nullptr)
			child_transf->RecalculateTransform();
	}
}

void ComponentTransf::DrawInInspector()
{
	if (ImGui::CollapsingHeader("Component Transformation"))
	{
		float3 pos = { position.x, position.y, position.z };
		float3 rot = { RadToDeg(quatRotation.ToEulerXYZ().x), RadToDeg(quatRotation.ToEulerXYZ().y), RadToDeg(quatRotation.ToEulerXYZ().z) };
		float3 sc = { scale.x,scale.y,scale.z };

		if (ImGui::DragFloat3("Position", (float*)&pos, 0.25f, -INFINITY, INFINITY))
		{
			/*if (!my_go->IsStatic())
			{
				position = { pos.x, pos.y, pos.z };
				RecalculateTransform();
			}*/
		}


		if (ImGui::DragFloat3("Rotation", (float*)&rot, 0.15f, -360, 360))
		{
			/*if (!my_go->IsStatic())
			{
				//TODO rotation
				RecalculateTransform();
			}*/
		}


		if (ImGui::DragFloat3("Scale", (float*)&sc, 0.05f, 0, INFINITY))
		{
			/*if (!my_go->IsStatic())
			{
				scale = { sc.x, sc.y, sc.z };
				RecalculateTransform();
			}*/

		}
	}
		

}
