#include "Configuration.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"


Configuration::Configuration(): Panel("Configuration")
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
		if (ImGui::CollapsingHeader("Renderer"))
		{
			if (ImGui::Checkbox("Wireframe", &App->renderer3D->wireframe)) App->renderer3D->update_wireframe();
			ImGui::SameLine();
			if (ImGui::Checkbox("Depth test", &App->renderer3D->depth_test)) App->renderer3D->update_depth_test();
			ImGui::SameLine();
			if (ImGui::Checkbox("Cull face", &App->renderer3D->cullface)) App->renderer3D->update_cullface();
			if (ImGui::Checkbox("Lighting", &App->renderer3D->lighting)) App->renderer3D->update_lighting();
			ImGui::SameLine();
			if (ImGui::Checkbox("Color Material", &App->renderer3D->color_material)) App->renderer3D->update_color_material();
			ImGui::SameLine();
			if (ImGui::Checkbox("Texture2D", &App->renderer3D->texture)) App->renderer3D->update_texture();
			if (ImGui::Checkbox("Smooth line", &App->renderer3D->line_smooth)) App->renderer3D->update_line_smooth();
		}
		if (ImGui::CollapsingHeader("Input"))
		{
			App->input->ShowInputConfiguration();
		}

		if (ImGui::CollapsingHeader("Hardware"))
		{
			ImGui::Text("CPUs: %d (Cache: %d kb)", hw.GetNumberCPU(), hw.GetCPUCache());
			ImGui::Text("System RAM: ");
			ImGui::TextColored(ImVec4(1, 1, 1, 1), "%i", SDL_GetSystemRAM());
			
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


