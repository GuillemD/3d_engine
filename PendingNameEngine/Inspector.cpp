#include "Inspector.h"
#include "Application.h"


Inspector::Inspector():Panel ("Inspector")
{
}


Inspector::~Inspector()
{
}

void Inspector::ShowElement()
{
	ImGui::Begin("Inspector");
	int i = 1;
	for (std::list<Mesh*>::iterator it = App->scene_intro->scene_objects.begin(); it != App->scene_intro->scene_objects.end(); it++)
	{
		
		ImGui::Text("Mesh %d: ", i);
		ImGui::Text("Total vertices: %d", (*it)->data.num_vertex);
		ImGui::Text("Total normals: %d", (*it)->data.num_normals);
		ImGui::Text("Total indices: %d", (*it)->data.num_index);
		ImGui::Separator();
		ImGui::Text("Position: { %.2f, %.2f, %.2f }", (*it)->t.pos.x, (*it)->t.pos.y, (*it)->t.pos.z);
		ImGui::Text("Scaling: { %.2f, %.2f, %.2f }", (*it)->t.scale.x, (*it)->t.scale.y, (*it)->t.scale.z);
		ImGui::Text("Rotation: { %.2f, %.2f, %.2f }", (*it)->t.rot.x, (*it)->t.rot.y, (*it)->t.rot.z);
		ImGui::Separator();
		
		
		ImTextureID tex = (uint*)(*it)->id_texture;
		ImVec2 size = ImGui::GetWindowSize();
		size.y = size.x;
		ImGui::Image(tex, size);
		i++;
	}
	ImGui::End();
	
}
