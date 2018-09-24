#pragma once
#ifndef Console_H
#define Console_H
#include "Globals.h"
#include "ImGui/imgui.h"

class Console
{
public:
	Console();
	~Console();
	void ConsoleLog(const char* log_text);
	void EmptyConsole();
	void CreateConsole();
private:
	ImGuiTextBuffer text;
};


#endif