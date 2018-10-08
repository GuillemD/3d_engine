#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "glmath.h"


#define MAX_LIGHTS 8


class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init(rapidjson::Document& document);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void DisableLight();  //Use this in the PostUpdate of a Module for it to ignore Scene Lights
	void EnableLight();


public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;

	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool show_plane = true;

	//attributes
	bool wireframe = false;
	bool depth_test = false;
	bool cullface = true;
	bool texture = true;
	bool color_material = true;
	bool lighting = true;
	bool line_smooth = false;
	bool v_normals_active = false;
	//swap-checkers
	void update_wireframe();
	void update_depth_test();
	void update_cullface();
	void update_texture();
	void update_color_material();
	void update_lighting();
	void update_line_smooth();

};