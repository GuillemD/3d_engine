#pragma once
#include "Panel.h"
#include "ImGui\imgui.h"

class Inspector : public Panel {
public:
	Inspector();
	~Inspector();

	void ShowElement();

};

