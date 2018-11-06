#include "ComponentTransf.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

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

void ComponentTransf::DrawInInspector()
{
	
		float3 pos = { position.x, position.y, position.z };
		float3 rot = { eulerRotation.x, eulerRotation.y, eulerRotation.z };
		float3 sc = { scale.x,scale.y,scale.z };

		if (ImGui::DragFloat3("Position", (float*)&pos, 0.25f, -INFINITY, INFINITY))
		{
			if (!my_go->staticgo)
			{
				position = { pos.x, pos.y, pos.z };
				//my_go->SetLocalPosition(position);
			}
		}
			

		if (ImGui::DragFloat3("Rotation", (float*)&rot, 0.15f, -360, 360))
		{
			if (!my_go->staticgo)
			{
				eulerRotation = { rot.x, rot.y, rot.z };
				//my_go->SetLocalRotation(eulerRotation);
			}
		}
			

		if (ImGui::DragFloat3("Scale", (float*)&sc, 0.05f, 0, INFINITY))
		{
			if (!my_go->staticgo)
			{
				scale = { sc.x, sc.y, sc.z };
				//my_go->SetLocalScale(scale);
			}
			
		}
			
	
	
}
