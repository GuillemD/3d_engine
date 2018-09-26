#include "Application.h"
#include "ModuleUI.h"
#include "Globals.h"
ModuleUI::ModuleUI( bool start_enabled) : Module(start_enabled)
{
	
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	LOG("Setting up UI");
	bool ret = true;
	ImGui_ImplSdl_Init(App->window->window);

	return ret;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplSdl_NewFrame(App->window->window);
	
	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	CreateMainMenu();
	
	if (ShowAbout) ShowAboutWindow();
	if (ShowTestWindow) ShowDemoWindow();
	if (ShowRNG) ShowRNGenerator();	

	if (ShowSphereCreatorPanel)ShowSphereCreator();
	if (ShowCubeCreatorPanel)ShowCubeCreator();
	if (ShowCapsuleCreatorPanel)ShowCapsuleCreator();

	if (closeApp) return UPDATE_STOP;


	console.CreateConsole();

	return UPDATE_CONTINUE;

}
update_status ModuleUI::PostUpdate(float dt)
{
	App->renderer3D->DisableLight();
	ImGui::Render();
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	LOG("Cleaning UI");
	ImGui_ImplSdl_Shutdown();
	return true;
}


void ModuleUI::ShowCubeCreator() {
	if (ImGui::Begin("Cube Creator Panel")) {
		ImGui::Text("AABB Min Positions");
		ImGui::InputFloat("MinX Positon", &tmpvec.x, 0.05f, 0, 3);
		ImGui::InputFloat("MinY Position", &tmpvec.y, 0.05f, 0, 3);
		ImGui::InputFloat("MinZ Position", &tmpvec.z, 0.05f, 0, 3);

		ImGui::Text("AABB Max Positions");
		ImGui::InputFloat("MaxX Positon", &tmpvec2.x, 0.05f, 0, 3);
		ImGui::InputFloat("MaxY Position", &tmpvec2.y, 0.05f, 0, 3);
		ImGui::InputFloat("MaxZ Position", &tmpvec2.z, 0.05f, 0, 3);

		if (ImGui::Button("Create Cube")) {
			App->physics->CreateCube(tmpvec, tmpvec2);
		}
	}
	ImGui::End();
}

void ModuleUI::ShowSphereCreator()
{
	if (ImGui::Begin("Sphere Creator Panel")) {

		ImGui::InputFloat("Radius", &tmpfloat, 0.05f, 0, 3);
		ImGui::InputFloat("X Positon", &tmpvec.x, 0.05f, 0, 3);
		ImGui::InputFloat("Y Position", &tmpvec.y, 0.05f, 0, 3);
		ImGui::InputFloat("Z Position", &tmpvec.z, 0.05f, 0, 3);

		if (ImGui::Button("Create Sphere")) {
			App->physics->CreateSphere(tmpvec, tmpfloat);
		}
	}
	ImGui::End();
}

void ModuleUI::ShowCapsuleCreator()
{
	if (ImGui::Begin("Capsule Creator Panel")) {

		ImGui::Text("Radius");
		ImGui::InputFloat("Radius", &tmpfloat, 0.05f, 0, 3);

		ImGui::Text("LineSegment Begin Positions");
		ImGui::InputFloat("BeginX Positon", &tmpvec.x, 0.05f, 0, 3);
		ImGui::InputFloat("BeginY Position", &tmpvec.y, 0.05f, 0, 3);
		ImGui::InputFloat("BeginZ Position", &tmpvec.z, 0.05f, 0, 3);

		ImGui::Text("LineSegment End Positions");
		ImGui::InputFloat("EndX Positon", &tmpvec2.x, 0.05f, 0, 3);
		ImGui::InputFloat("EndY Position", &tmpvec2.y, 0.05f, 0, 3);
		ImGui::InputFloat("EndZ Position", &tmpvec2.z, 0.05f, 0, 3);


		if (ImGui::Button("Create Capsule")) {
			App->physics->CreateCapsule(tmpfloat, LineSegment(tmpvec,tmpvec2));
		}

	}
	ImGui::End();
}

void ModuleUI::ShowDemoWindow()
{
	ImGui::ShowTestWindow();
}
void ModuleUI::ShowRNGenerator()
{
	if (ImGui::Begin("Random Number Generator using PCG"))
	{
		ImGui::InputInt("Insert first int", &input_min);
		ImGui::InputInt("Insert second int", &input_max);

		if (input_min == input_max)
		{
			rand_bounded_int = input_max = input_min;
		}
		else
		{
			if (input_min > input_max)
			{
				
				
				if (ImGui::Button("Generate Random Between given ints"))
				{
					Swap<int>(input_min, input_max);
					rand_bounded_int = (" %i", (int)pcg32_boundedrand_r(&rng1, input_max) + input_min);
				}
				ImGui::Text("%i", rand_bounded_int);
			}
			else
			{
				if (ImGui::Button("Generate Random Between given ints"))
				{
					rand_bounded_int = (" %i", (int)pcg32_boundedrand_r(&rng1, input_max) + input_min);
				}
				ImGui::Text("%i", rand_bounded_int);
			}
		}

		if (ImGui::Button("Generate Float between 0.0 and 1.0"))
		{
			rand_float = ldexp(pcg32_random_r(&rng1), -32);
		}
		ImGui::Text("%f", rand_float);
		ImGui::End();
	}
}
void ModuleUI::CreateMainMenu()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {

			if (ImGui::MenuItem("Show Random Number Generator")) {
				ShowRNG = !ShowRNG;
			}
			if (ImGui::MenuItem("Close Application")) {
				closeApp = !closeApp;
			}
			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu("Object creators")) {

			if (ImGui::MenuItem("Sphere creator panel")) {
				//bool to show the sphere creator
				ShowSphereCreatorPanel = !ShowSphereCreatorPanel;
			}
			if (ImGui::MenuItem("Cube creator panel")) {
				//bool to show the sphere creator
				ShowCubeCreatorPanel = !ShowCubeCreatorPanel;
			}
			if (ImGui::MenuItem("Capsule creator panel")) {
				//bool to show the sphere creator
				ShowCapsuleCreatorPanel = !ShowCapsuleCreatorPanel;
			}
			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu("Collision Checkers")) {
			if (ImGui::MenuItem("Sphere collision checkers")) {
				App->physics->GetSphereCollisionsList();
			}
			if (ImGui::MenuItem("Cube collision checkers")) {
				App->physics->GetCubeCollisionsList();
			}
			if (ImGui::MenuItem("Capsule collision checkers")) {
				App->physics->GetCapsuleCollisionsList();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("ImGui Demo Window")) {
				ShowTestWindow = !ShowTestWindow;
			}
			if (ImGui::MenuItem("Engine documentation")) {
				App->OpenBrowser("https://github.com/GuillemD/PendingNameEngine-3D/wiki");
			}
			if (ImGui::MenuItem("Latest Release")) {
				App->OpenBrowser("https://github.com/GuillemD/PendingNameEngine-3D/releases");
			}
			if (ImGui::MenuItem("Report Bugs")) {
				App->OpenBrowser("https://github.com/GuillemD/PendingNameEngine-3D/issues");
			}
			if (ImGui::MenuItem("About")) {
				ShowAbout = !ShowAbout;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
void ModuleUI::ShowAboutWindow()
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
			ImGui::Text("Copyright(c) 2019 Asier Arellano Moreno and Guillem Dominguez Ruiz de Villa");
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
