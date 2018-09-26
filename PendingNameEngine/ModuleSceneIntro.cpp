#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

#include "SDL/include/SDL_opengl.h"


ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	App->camera->Move(vec(0.0f, 50.0f, 0.0f));
	App->camera->LookAt(vec(0.0f, 0.0f, 0.0f));
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
update_status ModuleSceneIntro::Update(float dt)
{
	if (grid_active)
		DrawGrid();
	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::DrawGrid()
{

	glLineWidth(1.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);

	float d = 20.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
	/*glColor3f(.3, .3, .3);
	glBegin(GL_QUADS);
	glVertex3f(0, -0.001, 0);
	glVertex3f(0, -0.001, 2);
	glVertex3f(2, -0.001, 2);
	glVertex3f(2, -0.001, 0);
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i <= 10; i++) {
		if (i == 0) { glColor3f(.6, .3, .3); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 2);
		if (i == 0) { glColor3f(.3, .3, .6); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(0, 0, i);
		glVertex3f(2, 0, i);
	};
	glEnd();*/
}



