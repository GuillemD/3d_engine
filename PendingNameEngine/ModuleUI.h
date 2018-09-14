#pragma once

#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "imgui.h"


class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

};


#endif // __ModuleUI_H__
