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

	ScrollToBottom = true;
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



	if (ScrollToBottom)
		ImGui::SetScrollHere(1.0f);
	ScrollToBottom = false;

	ImGui::End();
}
