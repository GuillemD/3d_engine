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
		i++;
	}
	ImGui::End();
}
