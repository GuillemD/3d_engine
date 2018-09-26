#pragma once
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Globals.h"
#include "ImGui/imgui.h"
#include "Hardware.h"
#include "Panel.h"

class Configuration:public Panel
{
public:

	Configuration();
	~Configuration();

	void ShowElement();

	void PrintCaps(std::vector<bool> list);

	Hardware hw;

private:
	bool active = true;
	
	
};

#endif //__CONFIGURATION_H__
