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
	if (ShowSphereCreatorPanel) {
		if(ImGui::Begin("Sphere Creato Panel")) {
			tmpvec = vec(0.0f, 0.0f, 0.0f);
			ImGui::InputFloat("Radius", &tmpint);
			ImGui::InputFloat("X Positon", &tmpvec.x);
			ImGui::InputFloat("Y Position", &tmpvec.y);
			ImGui::InputFloat("Z Position",&tmpvec.z);
		}
		ImGui::End();
	}
	if (ShowCubeCreatorPanel) {
		if (ImGui::Begin("Cube Creator Panel")) {

		}
		ImGui::End();
	}
	if (ShowCapsuleCreatorPanel) {
		if (ImGui::Begin("Capsule Creator Panel")) {

		}
		ImGui::End();
	}


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
