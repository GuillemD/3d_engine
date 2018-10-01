#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "GLEW/include/glew.h"
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

	App->camera->Move(float3(0.0f, 10.0f, 10.0f));
	App->camera->LookAt(float3(0.0f, 3.0f, 0.0f));
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
void ModuleSceneIntro::Draw() const
{

	glLineWidth(2.0f);
	//DirectMode
	
	glBegin(GL_TRIANGLES);
	{
		//Front face
		glVertex3f(10.f, 10.f, 0.f);
		glVertex3f(0.f, 10.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);

		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(10.f, 10.f, 0.f);

		//Right face
		glVertex3f(10.f, 10.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(10.f, 0.f, -10.f);

		glVertex3f(10.f, 0.f, -10.f);
		glVertex3f(10.f, 10.f, -10.f);
		glVertex3f(10.f, 10.f, 0.f);

		//Top face
		glVertex3f(10.f, 10.f, 0.f);
		glVertex3f(10.f, 10.f, -10.f);
		glVertex3f(0.f, 10.f, -10.f);

		glVertex3f(0.f, 10.f, -10.f);
		glVertex3f(0.f, 10.f, 0.f);
		glVertex3f(10.f, 10.f, 0.f);

		//Back face
		glVertex3f(0.f, 0.f, -10.f);
		glVertex3f(10.f, 0.f, -10.f);
		glVertex3f(10.f, 10.f, -10.f);

		glVertex3f(10.f, 10.f, -10.f);
		glVertex3f(0.f, 10.f, -10.f);
		glVertex3f(0.f, 0.f, -10.f);

		//Left face
		glVertex3f(0.f, 0.f, -10.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 10.f, 0.f);

		glVertex3f(0.f, 10.f, 0.f);
		glVertex3f(0.f, 10.f, -10.f);
		glVertex3f(0.f, 0.f, -10.f);

		//Bottom face
		glVertex3f(0.f, 0.f, -10.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);

		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(10.f, 0.f, -10.f);
		glVertex3f(0.f, 0.f, -10.f);
	}
	glEnd();
	

	//VertexArray
	uint my_id = 0;

	std::vector<vec> vertices;
	{
	vertices.push_back(vec((10.f, 10.f, 0.f)));
	vertices.push_back(vec((0.f, 10.f, 0.f)));
	vertices.push_back(vec((0.f, 0.f, 0.f)));
	vertices.push_back(vec((10.f, 0.f, 0.f)));

	vertices.push_back(vec((10.f, 0.f, -10.f)));
	vertices.push_back(vec((10.f, 10.f, -10.f)));
	vertices.push_back(vec((10.f, 10.f, 0.f)));
	vertices.push_back(vec((0.f, 0.f, -10.f)));
	}
	/*
	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size()*3, &vertices.begin(), GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// ... draw other buffers
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	*/

	glLineWidth(1.0f);
	//geometry
}
update_status ModuleSceneIntro::Update(float dt)
{
	return UPDATE_CONTINUE;
}




