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
		ImGui::Begin("Inspector", &active);
		int i = 1;
		for (int j = 0 ;j < App->scene_loader->scene_objects.size(); j++)
		{
			

		}
		ImGui::End();
	}
	
	
}
