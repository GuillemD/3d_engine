#pragma once
#include "Globals.h"
#include <string>
class Panel
{
public:
	Panel(const char* name);
	virtual ~Panel();

	void Activate();
	bool IsActive();
	virtual void Draw();
public:
	bool active = true;
	int width, height, pos_x, pos_y;
	std::string name;


};