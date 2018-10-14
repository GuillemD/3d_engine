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
	if (active)
	{
		if (ImGui::Begin("Configuration", &active, ImGuiWindowFlags_NoCollapse))
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
				ImGui::Columns(3, NULL, false);
				if (ImGui::Checkbox("Wireframe", &App->renderer3D->wireframe)) App->renderer3D->update_wireframe();
				if (ImGui::Checkbox("Depth test", &App->renderer3D->depth_test)) App->renderer3D->update_depth_test();
				if (ImGui::Checkbox("Cull face", &App->renderer3D->cullface)) App->renderer3D->update_cullface();
				ImGui::NextColumn();
				if (ImGui::Checkbox("Lighting", &App->renderer3D->lighting)) App->renderer3D->update_lighting();
				if (ImGui::Checkbox("Color Material", &App->renderer3D->color_material)) App->renderer3D->update_color_material();
				if (ImGui::Checkbox("Texture2D", &App->renderer3D->texture)) App->renderer3D->update_texture();
				ImGui::NextColumn();
				if (ImGui::Checkbox("Smooth line", &App->renderer3D->line_smooth)) App->renderer3D->update_line_smooth();
				if (ImGui::Checkbox("Vertex Normals", &App->renderer3D->v_normals_active));
				ImGui::Columns(1, NULL, false);
				
			}
			if (ImGui::CollapsingHeader("Input"))
			{
				App->input->ShowInputConfiguration();
			}
			if (ImGui::CollapsingHeader("Camera"))
			{
				App->camera->ShowCameraConfiguration();
			}
			if (ImGui::CollapsingHeader("Hardware"))
			{
				ImGui::Text("CPUs: %d ", GetNumberCPU());
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(0, 1, 1, 1), "(Cache: %d kb)", GetCPUCache());
				ImGui::Text("System RAM: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "%d", GetRAM());

				ImGui::Separator();
				PrintCaps(GetCaps());

			}
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
int Configuration::GetNumberCPU() const
{
	int cpus = 0;

	cpus = SDL_GetCPUCount();
	return cpus;
}

int Configuration::GetCPUCache() const
{
	int cache = 0;
	cache = SDL_GetCPUCacheLineSize();
	return cache;
}

int Configuration::GetRAM() const
{
	int ram = 0;
	ram = SDL_GetSystemRAM();
	return ram;
}

std::vector<bool> Configuration::GetCaps()
{

	threednow = SDL_Has3DNow();
	avx = SDL_HasAVX();
	altivec = SDL_HasAltiVec();
	mmx = SDL_HasMMX();
	rdtsc = SDL_HasRDTSC();
	sse = SDL_HasSSE();
	sse2 = SDL_HasSSE2();
	sse3 = SDL_HasSSE3();
	sse41 = SDL_HasSSE41();
	sse42 = SDL_HasSSE42();

	if (threednow)
		caps.push_back(threednow);
	if (avx)
		caps.push_back(avx);
	if (altivec)
		caps.push_back(altivec);
	if (mmx)
		caps.push_back(mmx);
	if (rdtsc)
		caps.push_back(rdtsc);
	if (sse)
		caps.push_back(sse);
	if (sse2)
		caps.push_back(sse2);
	if (sse3)
		caps.push_back(sse3);
	if (sse41)
		caps.push_back(sse41);
	if (sse42)
		caps.push_back(sse42);

	return caps;
}



