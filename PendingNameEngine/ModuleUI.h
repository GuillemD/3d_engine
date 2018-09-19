#pragma once

#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"

#include "PCG/pcg_basic.h"

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();


private:
	bool ShowTestWindow = false;
	bool ShowRNG = false;

public:
	pcg32_random_t rng1 = PCG32_INITIALIZER;

	int input_min = 0; int input_max = 0;
	
	int rand_bounded_int = 0;
	float rand_float = 0.0f;
};


#endif // __ModuleUI_H__
