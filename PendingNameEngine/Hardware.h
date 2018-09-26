#pragma once
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "SDL\include\SDL_cpuinfo.h"
#include <vector>

class Hardware
{
public:
	Hardware();
	~Hardware();

	int GetNumberCPU() const;
	int GetCPUCache() const;
	float GetRAM() const;

	std::vector<bool> GetCaps();
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


#endif // !__HARDWARE_H__

