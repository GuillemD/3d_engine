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
	App->camera->Move(vec(0.0f, 10.0f, 0.0f));
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
	glEnableClientState(GL_VERTEX_ARRAY);
	struct vertex
	{
		GLfloat x, y, z;
	};
	vertex *vertices = new vertex[3];

	// Assign some values to all 3 points
	vertices[0].x = 10.0f;
	vertices[0].y = 5.0f;
	vertices[0].z = 7.0f;

	// Vertex 2
	vertices[1].x = -10.0f;
	vertices[1].y = 3.0f;
	vertices[1].z = 1.0f;

	// Vertex 3
	vertices[2].x = 5.0f;
	vertices[2].y = -5.0f;
	vertices[2].z = 2.0f;

	glVertexPointer(3, GL_FLOAT,sizeof(vertex), vertices);

	int num_indices = 3;
	glDrawArrays(GL_TRIANGLES, 0, num_indices);
	
	
}



