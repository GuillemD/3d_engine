#pragma once

#ifndef __ABOUT_H__
#define __ABOUT_H__
#include "Globals.h"
#include "ImGui/imgui.h"

class About
{
public:
	About();
	~About();
	
	
	void ShowElement();
	void SwitchActive();
	bool active = false;

	
};


#endif