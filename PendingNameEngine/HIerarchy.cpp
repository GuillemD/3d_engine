#include "Hierarchy.h"
#include "Application.h"
#include "ModuleSceneLoader.h"

Hierarchy::Hierarchy() : Panel("Hierarchy")
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::CreateHierarchy()
{
	if (active)
	{
		ImGui::Begin("Hierarchy", &active);

		App->scene_loader->DrawHierarchy();

		ImGui::End();
		
	}
	
}
