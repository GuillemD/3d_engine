#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"
class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init(rapidjson::Document& document);
	bool CleanUp();

	void SetTitle(const char* title);
	void ShowWindowConfiguration();

	bool Save(rapidjson::Document& document, rapidjson::FileWriteStream& os);
	bool Load(rapidjson::Document& document);


	bool fullscreen = WIN_FULLSCREEN;
	bool borderlessfullscreen = WIN_BORDERLESS;
	bool resizable = WIN_RESIZABLE;
	bool fullscreendesktop = WIN_FULLSCREEN_DESKTOP;

public:
	//The window we'll be rendering to
	SDL_Window* window;
	Uint32 flags;
	int width;
	int height;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__