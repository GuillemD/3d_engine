#include "About.h"
#include "Application.h"

About::About()
{
}

About::~About()
{
}

void About::ShowElement()
{
	if (active)
	{
		if (ImGui::Begin("About"))
		{
			ImGui::Text("PendingName Engine made by Asier Arellano and Guillem Dominguez for academic purposes %s", App->GetVersion());
			ImGui::Spacing();
			ImGui::Separator();

			ImGui::Text("SDL v2.0.4");
			ImGui::Text("MathGeoLib v?");
			ImGui::Text("PCG Minimal C Edition");
			ImGui::Text("Parson v?");
			ImGui::Text("ImGui v1.64");

			ImGui::Separator();

			if (ImGui::CollapsingHeader("LICENSE"))
			{
				ImGui::Text("MIT License");
				ImGui::Text("Copyright(c) 2018 Asier Arellano Moreno and Guillem Dominguez Ruiz de Villa");
				ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy of this");
				ImGui::Text("software and associated documentation files(the 'Software'), to deal in the");
				ImGui::Text("Software without restriction, including without limitation the rights to use, copy,");
				ImGui::Text("modify, merge, publish, distribute, sublicense, and / or sell copies of the Software,");
				ImGui::Text("and to permit persons to whom the Software is furnished to do so,");
				ImGui::Text("subject to the following conditions :");

				ImGui::Text("The above copyright notice and this permission notice shall be included in all");
				ImGui::Text("copies or substantial portions of the Software.");

				ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,");
				ImGui::Text("INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A");
				ImGui::Text("PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT");
				ImGui::Text("HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION");
				ImGui::Text("OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH");
				ImGui::Text("THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");

			}

		}
		ImGui::End();
	}
	
	
}

void About::SwitchActive()
{
	active = !active;
}
