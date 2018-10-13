#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "TextureLoader.h"
#include "ModuleSceneLoader.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleUI.h"
#include "Importer.h"
#include <list>
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\filewritestream.h"

class Configuration;

class Application
{
public:
	ModuleWindow* window;
	ModuleAudio* audio;
	Importer* importer;
	TextureLoader* texture;
	ModuleInput* input;
	ModuleSceneLoader* scene_loader;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	ModuleUI* ui;


private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> list_modules;

	std::string app_name;
	std::string org_name;
	std::string app_version;

	std::vector<float>	FPSBars;
	std::vector<float>	MillisecondsBars;
	std::vector<float>	MemoryBars;

	uint TotalFrameCount = 0;
	uint ThisSecFrameCount = 0;
	uint LastSecFrameCount = 0;
	Uint32 LastSecMs = 0;
	Timer LastSecondFrameTimer;
	Timer MsSinceStart;
	float AverageFPS = 0;
	bool vsync = VSYNC;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	
	void OpenBrowser(const char* url);
	void OpenFile(const char* path);
	const char* GetVersion() const;
	void SetVersion(const char* version);
	const char* GetAppName() const;
	void SetAppName(const char* app);
	const char* GetOrgName() const;
	void SetOrgName(const char* org);
	void ShowApplicationCongfig();

	bool SaveConfig();
	bool LoadConfig();


private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	


};
extern Application* app;