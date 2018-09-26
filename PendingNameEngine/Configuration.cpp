#include "Configuration.h"
#include "Application.h"
#include "ModuleWindow.h"


Configuration::Configuration():Panel("Configuration")
{
}

Configuration::~Configuration()
{
}

void Configuration::ShowElement()
{
	if (ImGui::Begin("Configuration",&active,ImGuiWindowFlags_NoCollapse ))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::Text("App Name: %s ", App->GetAppName());
			ImGui::SameLine();
			ImGui::Text("Version: %s", App->GetVersion());
			ImGui::Text("Org Name: %s", App->GetOrgName());
			ImGui::Separator();
			App->ShowApplicationCongfig();
		}
		if (ImGui::CollapsingHeader("Window"))
		{
			App->window->ShowWindowConfiguration();
		}
		if (ImGui::CollapsingHeader("Input"))
		{
			App->input->ShowInputConfiguration();
		}
		if (ImGui::CollapsingHeader("Hardware"))
		{
			ImGui::Text("CPUs: %d (Cache: %d kb)", hw.GetNumberCPU(), hw.GetCPUCache());
			ImGui::Text("System RAM: "); ImGui::SameLine(0, 10);
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%i", SDL_GetSystemRAM());
			
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


