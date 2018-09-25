#include "Configuration.h"
#include "Application.h"
#include "ModuleWindow.h"
Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

void Configuration::ShowElement()
{
	if (ImGui::Begin("Configuration",&active,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse ))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::Text("App Name: %s ", App->GetAppName());
			ImGui::SameLine();
			ImGui::Text("Version: %s", App->GetVersion());
			ImGui::Text("Org Name: %s", App->GetOrgName());
			ImGui::Separator();

		}
		if (ImGui::CollapsingHeader("FileSystem"))
		{

		}
		if (ImGui::CollapsingHeader("Window"))
		{
			App->window->ShowWindowConfiguration();
		}
		if (ImGui::CollapsingHeader("Input"))
		{

		}
		if (ImGui::CollapsingHeader("Hardware"))
		{

		}
		ImGui::End();
	}
}


