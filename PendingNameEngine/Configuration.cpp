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
		if (ImGui::CollapsingHeader("Window"))
		{
			App->window->ShowWindowConfiguration();
		}
		if (ImGui::CollapsingHeader("Input"))
		{

		}
		if (ImGui::CollapsingHeader("Hardware"))
		{
			ImGui::Text("CPUs: %d (Cache: %d kb)", hw.GetNumberCPU(), hw.GetCPUCache());
			ImGui::Text("System RAM: %d", hw.GetRAM());
			
			PrintCaps(hw.GetCaps());


		}
		ImGui::End();
	}
}

void Configuration::PrintCaps(std::vector<bool> vec)
{
	
	const char* caps[10] = { "3DNOW", "AVX", "ALTIVEC", "MMX", "RDTSC", "SSE", "SSE2", "SSE3", "SSE41", "SSE42" };

	for (int i = 0; i < 10; i++)
	{
		if (vec[i] == true)
		{
			ImGui::Text(caps[i]);
		}else
			ImGui::Text("");		

	}
}


