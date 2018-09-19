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

			
			if (ImGui::MenuItem("Show Test Window")) {
				if (ShowTestWindow) {
					ShowTestWindow = false;
				}
				else
				{
					ShowTestWindow = true;
				}
			}
			if (ImGui::MenuItem("Show Random Number Generator")) {
				if (ShowRNG) {
					ShowRNG = false;
				}
				else
				{
					ShowRNG = true;
				}
			}
			if (ImGui::MenuItem("Close Application")) {
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
	}

	ImGui::EndMainMenuBar();
	if (ShowTestWindow) {
		ImGui::ShowTestWindow();
	}
	if (ShowRNG)
	{
		

		if (ImGui::Begin("Random Number Generator using PCG"))
		{
			ImGui::InputInt("Insert first int", &input_min);
			ImGui::InputInt("Insert second int", &input_max);

			if (input_min > input_max)
			{
				if (ImGui::Button("Generate Random Between given ints"))
				{
					rand_bounded_int = (" %i", (int)pcg32_boundedrand_r(&rng1, input_min) + input_max);
				}
				ImGui::Text("%i", rand_bounded_int);
			}
			else
			{
				if (ImGui::Button("Generate Int"))
				{
					rand_bounded_int = (" %i", (int)pcg32_boundedrand_r(&rng1, input_max) + input_min);
				}
				ImGui::Text("%i", rand_bounded_int);
			}

			
			if (ImGui::Button("Generate Float between 0.0 and 1.0"))
			{
				rand_float = ldexp(pcg32_random_r(&rng1), -32);
			}
			ImGui::Text("%f", rand_float);
			ImGui::End();
		}
		
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
