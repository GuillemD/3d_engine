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
	
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("Menu")) {

			
			if (ImGui::MenuItem("ShowTestWindow")) {
				ShowTestWindow = !ShowTestWindow;
			}


			if (ImGui::MenuItem("Close Application")) {
				return UPDATE_STOP;
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
		
	}

	ImGui::EndMainMenuBar();
	if (ShowTestWindow) {
		ImGui::ShowTestWindow();
	}

	if (ShowSphereCreatorPanel)ShowSphereCreator();
	if (ShowCubeCreatorPanel)ShowCubeCreator();
	if (ShowCapsuleCreatorPanel)ShowCapsuleCreator();


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
