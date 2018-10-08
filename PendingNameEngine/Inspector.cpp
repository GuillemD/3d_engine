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
	for (std::list<Mesh*>::iterator it = App->scene_intro->scene_objects.begin(); it != App->scene_intro->scene_objects.end(); it++)
	{
		ImGui::Text("num vertices: %d", (*it)->data.num_vertex);
	}
	ImGui::End();
}
