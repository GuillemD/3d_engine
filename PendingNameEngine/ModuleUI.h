#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "MathGeoLib/MathGeoLib.h"
#include "PCG/pcg_basic.h"
#include "Console.h"
#include "About.h"
#include "Configuration.h"
#include "Inspector.h"

class ModuleUI : public Module
{
public:
	ModuleUI(bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	Console console;
	About about;
	Configuration confg;
	Inspector insp;
	bool CleanUp();

	void DrawImGui();

private:
	
	//Checkers
	bool closeApp = false;
	bool ShowTestWindow = false;

	float tmpfloat = 0.0f;

	vec tmpvec = vec(0.0f, 0.0f, 0.0f);
	vec tmpvec2 = vec(0.0f, 0.0f, 0.0f);

private:

	void ModuleUI::ShowDemoWindow();
	void ModuleUI::ShowRNGenerator();

	void CreateMainMenu();
	
public:
	pcg32_random_t rng1 = PCG32_INITIALIZER;

	int input_min = 0; int input_max = 0;
	
	int rand_bounded_int = 0;
	float rand_float = 0.0f;

};
#endif // __ModuleUI_H__
