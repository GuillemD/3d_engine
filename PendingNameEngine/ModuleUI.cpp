#include "Application.h"
#include "ModuleUI.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
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
				ShellExecuteA(NULL, "open", "https://github.com/GuillemD/PendingNameEngine-3D/wiki", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Latest Release")) {
				ShellExecuteA(NULL, "open", "https://github.com/GuillemD/PendingNameEngine-3D/releases", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Report Bugs")) {
				ShellExecuteA(NULL, "open", "https://github.com/GuillemD/PendingNameEngine-3D/issues", NULL, NULL, SW_SHOWNORMAL);
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
		ImGui::Text("PendingName Engine made by Asier Arellano and Guillem Dominguez for academic purposes.");
		ImGui::Spacing();
		ImGui::Separator();

		ImGui::Text("SDL v2.0");
		//ShellExecuteA(NULL, "open", "https://www.libsdl.org/", NULL, NULL, SW_SHOWNORMAL);
	}
	ImGui::End();
	
}
