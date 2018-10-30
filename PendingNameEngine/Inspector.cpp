#include "Inspector.h"
#include "Application.h"
#include "ModuleSceneLoader.h"
#include "ComponentMesh.h"


Inspector::Inspector():Panel ("Inspector")
{
}


Inspector::~Inspector()
{
}

void Inspector::ShowElement()
{
	if (active)
	{
		ImGui::Begin("Inspector");
		int i = 1;
		for (int j = 0 ;j < App->scene_loader->scene_objects.size(); j++)
		{
			

			/*ImGui::Text("Total normals: %d", );
			ImGui::Text("Total indices: %d", );
			ImGui::Separator();
			ImGui::Text("Position: { %.2f, %.2f, %.2f }", (*it)->t.pos.x, (*it)->t.pos.y, (*it)->t.pos.z);
			ImGui::Text("Scaling: { %.2f, %.2f, %.2f }", (*it)->t.scale.x, (*it)->t.scale.y, (*it)->t.scale.z);
			ImGui::Text("Rotation: { %.2f, %.2f, %.2f }", (*it)->t.rot.x, (*it)->t.rot.y, (*it)->t.rot.z);
			ImGui::Separator();*/


			/*ImTextureID tex = (uint*)(*it)->id_texture;
			ImVec2 size = ImGui::GetWindowSize();
			size.y = size.x;
			ImGui::Image(tex, size);
			i++;*/
		}
		ImGui::End();
	}
	
	
}
