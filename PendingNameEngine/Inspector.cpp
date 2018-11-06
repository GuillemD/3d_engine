#include "Inspector.h"
#include "Application.h"
#include "ModuleSceneLoader.h"
#include "GameObject.h"



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
		
		for (int j = 0 ;j < App->scene_loader->scene_objects.size(); j++)
		{
			App->scene_loader->scene_objects[j]->DrawInInspector();

		}
		ImGui::End();
	}
	
	
}
