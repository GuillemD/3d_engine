#include "Configuration.h"

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

void Configuration::ShowElement()
{
	if (ImGui::Begin("Configuration"))
	{
		if (ImGui::CollapsingHeader("Application"))
		{

		}
		if (ImGui::CollapsingHeader("FileSystem"))
		{

		}
		if (ImGui::CollapsingHeader("Window"))
		{

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


