#pragma once
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Globals.h"
#include "ImGui/imgui.h"
#include "Panel.h"
#include "SDL\include\SDL_cpuinfo.h"

#include <vector>


class Configuration : public Panel
{
public:

	Configuration();
	~Configuration();

	void ShowElement();

	//hardware info
	void PrintCaps(std::vector<bool> list);

	int GetNumberCPU() const;
	int GetCPUCache() const;
	int GetRAM() const;

	std::vector<bool> GetCaps();


public:
	bool active = true;

private:
	std::vector<bool> caps;

	bool threednow = false;
	bool avx = false;
	bool altivec = false;
	bool mmx = false;
	bool rdtsc = false;
	bool sse = false;
	bool sse2 = false;
	bool sse3 = false;
	bool sse41 = false;
	bool sse42 = false;
	
	
};

#endif //__CONFIGURATION_H__
