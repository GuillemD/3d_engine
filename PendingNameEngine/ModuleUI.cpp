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
	about.ShowElement();
	confg.ShowElement();
	insp.ShowElement();
	if (ShowTestWindow) ShowDemoWindow();
	if (closeApp) return UPDATE_STOP;
	console.CreateConsole();

	return UPDATE_CONTINUE;

}
update_status ModuleUI::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}
void ModuleUI::DrawImGui() {
	
	App->renderer3D->DisableLight();
	bool auxwireframe = App->renderer3D->wireframe;
	bool auxcolor = App->renderer3D->color_material;
	
	if (App->renderer3D->wireframe || !auxcolor) {
		if (App->renderer3D->wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (!App->renderer3D->color_material) {
			glEnable(GL_COLOR_MATERIAL);
		}
		ImGui::Render();    

		if (auxwireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (!auxcolor) {
			glDisable(GL_COLOR_MATERIAL);
		}
	}
	else ImGui::Render();
}

bool ModuleUI::CleanUp()
{
	LOG("Cleaning UI");
	ImGui_ImplSdl_Shutdown();
	return true;
}


void ModuleUI::ShowDemoWindow()
{
	ImGui::ShowTestWindow();
}
void ModuleUI::ShowRNGenerator()
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

}
void ModuleUI::CreateMainMenu()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			if (ImGui::MenuItem("Save config"))
				App->SaveConfig();
			if (ImGui::MenuItem("Close Application")) {
				closeApp = !closeApp;
			}
			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu("Options")) {
			if (ImGui::BeginMenu("Show Panels"))
			{
				if (ImGui::Checkbox("Configuration", &confg.active));
				if (ImGui::Checkbox("Inspector", &insp.active));
				if (ImGui::Checkbox("Console", &console.active));

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Hide all panels"))
			{
				if (confg.active == true) confg.active = false;
				if (insp.active == true) insp.active = false;
				if (console.active == true) console.active = false;
				if (about.active == true) about.active = false;

			}
			if (ImGui::MenuItem("Delete Meshes"))
				App->scene_loader->scene_objects.clear();
			ImGui::Separator();
			if (ImGui::BeginMenu("Miscelaneous"))
			{
				if (ImGui::BeginMenu("ImGui Demo Window"))
				{
					if (ImGui::Button("Show"))
					{
						if (!ShowTestWindow)ShowTestWindow = true;
					}
					ImGui::SameLine();
					if (ImGui::Button("Hide"))
					{
						if (ShowTestWindow) ShowTestWindow = false;
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("RNG"))
				{
					ShowRNGenerator();
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
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
				about.SwitchActive();
				
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

