#include "Application.h"
#include "Globals.h"
#include "Configuration.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	importer = new Importer(this);
	texture = new TextureLoader(this);
	SM = new SerializationManager(this);
	ui = new ModuleUI(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	
	scene_loader = new ModuleSceneLoader(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(importer);
	AddModule(texture);
	AddModule(input);
	AddModule(ui);
	AddModule(SM);

	// Scenes
	AddModule(scene_loader);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); item++) {
		delete(*item);
	}
}

bool Application::Init()
{
	bool ret = true;

	SetAppName("PendingNameEngine");
	SetVersion("v1.1.0");
	SetOrgName("UPC CITM");

	rapidjson::Document document;
	FILE* fp = fopen("config.json", "rb");
	char readBuffer[65536];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	document.ParseStream(is);


	// Call Init() in all modules

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); item++) {
		ret = (*item)->Init(document);
	}

	//After we call all Init() we call all Starts
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); item++) {
		ret = (*item)->Start();
	}

	fclose(fp);
	ms_timer.Start();
	MsSinceStart.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}


// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret==UPDATE_CONTINUE; item++) {
		ret = (*item)->PreUpdate(dt);
	}
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++) {
		ret = (*item)->Update(dt);
	}
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++) {
		ret = (*item)->PostUpdate(dt);
	}

	// FPS stuff for Application Config Window

	ThisSecFrameCount++; // We add 1 each time we update, 1 time per frame
	TotalFrameCount++; //This one is used for calculating our average fps, so we add 1 each time also.
	//its important to do this before, otherwise we would show 1 less fps.

	AverageFPS = TotalFrameCount / (MsSinceStart.Read()/1000.0f);

	if (LastSecondFrameTimer.Read()>=1000) { // Basically if a whole 1000ms(1s) has passed restart the frame timer.
		LastSecondFrameTimer.Start();
		LastSecFrameCount = ThisSecFrameCount; //We store this second frames in the previous one
		ThisSecFrameCount = 0;					// and then we restart the frame count
	}



	// We will only show 30 bars in our histogram

	if (FPSBars.size() >= 100)
	{
		for (int a = 0; a <= FPSBars.size() - 2; a++)
		{
			FPSBars[a] = FPSBars[a + 1];
		}
		FPSBars.pop_back();
	}
	if (MillisecondsBars.size() >= 100)
	{
		for (int a = 0; a <= MillisecondsBars.size() - 2; a++)
		{
			MillisecondsBars[a] = MillisecondsBars[a + 1];
		}
		MillisecondsBars.pop_back();
	}

	LastSecMs = ms_timer.Read();
	MillisecondsBars.push_back((float)LastSecMs);
	if (LastSecMs) FPSBars.push_back((float)(1000/LastSecMs));

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); item++) {
		ret = (*item)->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::OpenBrowser(const char * url)
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}
void Application::OpenFile(const char * path)
{
	ShellExecute(NULL, NULL, path, NULL, NULL, SW_SHOW);
}

const char * Application::GetVersion() const
{
	return app_version.c_str();
}

void Application::SetVersion(const char * version)
{
	if (version != nullptr)
	{
		app_version = version;
	}
}

const char * Application::GetAppName() const
{
	return app_name.c_str();
}

void Application::SetAppName(const char * app)
{
	if (app != nullptr)
	{
		app_name = app;
	}
}

const char * Application::GetOrgName() const
{
	return org_name.c_str();
}

void Application::SetOrgName(const char * org)
{
	if (org != nullptr)
	{
		org_name = org;
	}
}

void Application::ShowApplicationCongfig()
{
	char title[30];

	if(ImGui::Checkbox("Vsync",&vsync)){
		if (vsync) {
			SDL_GL_SetSwapInterval(1);
		}
		else {
			SDL_GL_SetSwapInterval(0);
		}
	}

	sprintf_s(title, 30, "Frames per second: %.1f", App->FPSBars[App->FPSBars.size() - 1]);
	ImGui::PlotHistogram("", &App->FPSBars[0], App->FPSBars.size(), 0, title, 0.0f, 120.0f, ImVec2(310, 100));

	sprintf_s(title, 30, "ms: %.1f", App->MillisecondsBars[App->MillisecondsBars.size() - 1]);
	ImGui::PlotHistogram("", &App->MillisecondsBars[0], App->MillisecondsBars.size(), 0, title, 0.0f, 120.0f, ImVec2(310, 100));

}

bool Application::LoadConfig()
{
	bool ret = false;

	rapidjson::Document document;
	FILE* fp = fopen("config.json", "rb");
	char readBuffer[65536];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	document.ParseStream(is);
	fclose(fp);

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->Load(document);
	}

	return ret;
}

void Application::CreateNewDirectory(const char * output_directory) const
{

	if (!CreateDirectory(output_directory, NULL))
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			CONSOLELOG("Folder already exists");
			return;
		}
		else if (ERROR_PATH_NOT_FOUND == GetLastError())
		{
			CONSOLELOG("Path not found");
			return;
		}
			
	}
	
}

bool Application::FileCopy(const char * file_to_copy, const char * output_directory)
{
	bool ret = true;

	std::string curr_file = file_to_copy;
	uint cut = curr_file.find_last_of("\\");
	std::string dest_file = output_directory;
	if (dest_file.find_last_of("\\") == dest_file.size() - 1)
		dest_file += curr_file.substr(cut + 1, curr_file.size() - cut + 1);
	else
		dest_file += curr_file.substr(cut, curr_file.size() - cut);

	ret = CopyFile(file_to_copy, dest_file.c_str(), false);

	return ret;
}

bool Application::SaveConfig()
{
	bool ret = true;

	rapidjson::Document document;
	document.SetObject();
	FILE* fp = fopen("config.json", "wb");
	char writeBuffer[655360];

	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	document.MemberBegin();
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == true; item++)
	{
		ret = (*item)->Save(document, os);
	}
	document.MemberEnd();
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	document.Accept(writer);

	fclose(fp);

	return ret;
}
