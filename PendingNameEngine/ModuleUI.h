#pragma once

#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"

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
};


#endif // __ModuleUI_H__
