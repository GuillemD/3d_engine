#include "ComponentMaterial.h"
#include "GameObject.h"
#include "Material.h"
#include "ImGui/imgui.h"

ComponentMaterial::ComponentMaterial()
{
	MyType = MATERIAL;
	name = "Material Component";
}
ComponentMaterial::ComponentMaterial(GameObject* _gameobject)
{
	if (_gameobject != nullptr) {
		my_go = _gameobject;
		MyType = MATERIAL;
		name = "Material Component";
	}
}
ComponentMaterial::~ComponentMaterial()
{
}

void ComponentMaterial::DrawInInspector()
{
	
	if (mat != nullptr)
	{
		if (ImGui::CollapsingHeader("Component Material"))
		{
			ImGui::Text("Texture Height: %d", mat->GetHeight());
			ImGui::Text("Texture Width: %d", mat->GetWidth());
			ImGui::Text("Texture ID: %d", mat->GetID());
			ImGui::Separator();

			ImTextureID id = (uint*)mat->GetID();
			ImVec2 size = ImGui::GetWindowSize();
			size.x = size.x / 2;
			size.y = size.x;
			ImGui::Image(id, size);
		}
	}
}
