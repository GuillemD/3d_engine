#include "Hardware.h"

Hardware::Hardware()
{
	threednow = SDL_Has3DNow();
	avx = SDL_HasAVX();
	altivec = SDL_HasAltiVec();
	mmx = SDL_HasMMX();
	rdtsc = SDL_HasRDTSC();
	sse = SDL_HasSSE();
	sse2 = SDL_HasSSE2();
	sse3 = SDL_HasSSE3();
	sse41 = SDL_HasSSE41();
	sse42 = SDL_HasSSE42();

}

Hardware::~Hardware()
{
}

int Hardware::GetNumberCPU() const
{
	int cpus = 0;

	cpus = SDL_GetCPUCount();
	return cpus;
}

int Hardware::GetCPUCache() const
{
	int cache = 0;
	cache = SDL_GetCPUCacheLineSize();
	return cache;
}

float Hardware::GetRAM() const
{
	float ram = 0.f;
	ram = SDL_GetSystemRAM();
	return ram;
}

std::vector<bool> Hardware::GetCaps() 
{
	if (threednow)
		caps.push_back(threednow);
	if (avx)
		caps.push_back(avx);
	if (altivec)
		caps.push_back(altivec);
	if (mmx)
		caps.push_back(mmx);
	if (rdtsc)
		caps.push_back(rdtsc);
	if (sse)
		caps.push_back(sse);
	if (sse2)
		caps.push_back(sse2);
	if (sse3)
		caps.push_back(sse3);
	if (sse41)
		caps.push_back(sse41);
	if (sse42)
		caps.push_back(sse42);
	
	return caps;
}


