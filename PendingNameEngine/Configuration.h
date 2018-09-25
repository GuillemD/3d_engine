#pragma once
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Globals.h"
#include "ImGui/imgui.h"

class Configuration
{
public:

	Configuration();
	~Configuration();

	void ShowElement();


private:
	bool active = true;
	
	
};

#endif //__CONFIGURATION_H__
