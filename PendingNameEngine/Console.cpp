#include "Console.h"

Console::Console() :Panel("Console")
{
	width = 750;
	height = 300;
	pos_x = 300;
	pos_y = 1050;
}

Console::~Console()
{
}

void Console::ConsoleLog(const char* log_text) {
	text.append(log_text);
}

void Console::EmptyConsole()
{
	text.clear();
}

void Console::CreateConsole()
{
	ImGui::Begin("Console");
	if(ImGui::Button("Clear Console")) {
		EmptyConsole();
		CONSOLELOG("Console cleared correctly.");
	}
	ImGui::TextUnformatted(text.begin());
	
	ImGui::End();
}
