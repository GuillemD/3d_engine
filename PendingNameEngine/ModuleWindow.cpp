#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ImGui/imgui.h"

#include "rapidjson\document.h"

ModuleWindow::ModuleWindow(bool start_enabled) : Module(start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init(rapidjson::Document& document)
{
	LOG("Init SDL window & surface");
	bool ret = true;

	rapidjson::Value& configwindow = document["window"];





	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		width = configwindow["width"].GetInt();
		height = configwindow["height"].GetInt();
		
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 3.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		//Atributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


		if(fullscreen)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(resizable)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(borderlessfullscreen)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(fullscreendesktop)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::ShowWindowConfiguration()
{
	if (ImGui::SliderInt("Height", &height, 600, 1080)) {
		SDL_SetWindowSize(window, width, height);
	}
	if (ImGui::SliderInt("Width", &width, 600, 1920)) {
		SDL_SetWindowSize(window, width, height);
	}
	
	

	if (ImGui::Checkbox("Fullscreen",&fullscreen)){
		if (fullscreen) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
		else {
			SDL_SetWindowFullscreen(window, 0);
		}
	}
	if (ImGui::Checkbox("Borderless", &borderlessfullscreen)) {
		if (borderlessfullscreen) {
			
			SDL_SetWindowBordered(window, SDL_FALSE);
		}
		else {
			SDL_SetWindowBordered(window, SDL_TRUE);
		}
	}

	if (ImGui::Checkbox("Fullscreen Desktop", &fullscreendesktop)) {
		if (borderlessfullscreen) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else {
			SDL_SetWindowFullscreen(window, 0);
		}
	}


}

bool ModuleWindow::Save(rapidjson::Document & document, rapidjson::FileWriteStream & os)
{

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	
	rapidjson::Value Obj(rapidjson::kObjectType);
	Obj.AddMember("width", width, allocator);
	Obj.AddMember("height", height, allocator);
	
	document.AddMember("window", Obj, allocator);

	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);


	


	return true;
}

bool ModuleWindow::Load(rapidjson::Document & document)
{
	return true;
}


