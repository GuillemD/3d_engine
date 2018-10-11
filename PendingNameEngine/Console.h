#pragma once
#ifndef Console_H
#define Console_H
#include "Globals.h"
#include "ImGui/imgui.h"
#include "Panel.h"

class Console : public Panel
{
public:
	Console();
	~Console();
	void ConsoleLog(const char* log_text);
	void EmptyConsole();
	void CreateConsole();
	bool ScrollToBottom = false;
private:
	ImGuiTextBuffer text;
};


#endif