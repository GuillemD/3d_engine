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
	
	VertexAndIndexCube.DefineVerticesAndIndicesForACube(vec(-12.f, 0.f, -10.f), 10);
	VertexArrayCube.DefineVerticesForACube(vec(14.f, 0.f, -10.f), 10);
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
		glVertex3f(12.f, 10.f, 0.f);
		glVertex3f(2.f, 10.f, 0.f);
		glVertex3f(2.f, 0.f, 0.f);

		glVertex3f(2.f, 0.f, 0.f);
		glVertex3f(12.f, 0.f, 0.f);
		glVertex3f(12.f, 10.f, 0.f);

		//Right face
		glVertex3f(12.f, 10.f, 0.f);
		glVertex3f(12.f, 0.f, 0.f);
		glVertex3f(12.f, 0.f, -10.f);

		glVertex3f(12.f, 0.f, -10.f);
		glVertex3f(12.f, 10.f, -10.f);
		glVertex3f(12.f, 10.f, 0.f);

		//Top face
		glVertex3f(12.f, 10.f, 0.f);
		glVertex3f(12.f, 10.f, -10.f);
		glVertex3f(2.f, 10.f, -10.f);

		glVertex3f(2.f, 10.f, -10.f);
		glVertex3f(2.f, 10.f, 0.f);
		glVertex3f(12.f, 10.f, 0.f);

		//Back face
		glVertex3f(2.f, 0.f, -10.f);
		glVertex3f(12.f, 0.f, -10.f);
		glVertex3f(12.f, 10.f, -10.f);

		glVertex3f(12.f, 10.f, -10.f);
		glVertex3f(2.f, 10.f, -10.f);
		glVertex3f(2.f, 0.f, -10.f);

		//Left face
		glVertex3f(2.f, 0.f, -10.f);
		glVertex3f(2.f, 0.f, 0.f);
		glVertex3f(2.f, 10.f, 0.f);

		glVertex3f(2.f, 10.f, 0.f);
		glVertex3f(2.f, 10.f, -10.f);
		glVertex3f(2.f, 0.f, -10.f);

		//Bottom face
		glVertex3f(2.f, 0.f, -10.f);
		glVertex3f(2.f, 0.f, 0.f);
		glVertex3f(12.f, 0.f, 0.f);

		glVertex3f(12.f, 0.f, 0.f);
		glVertex3f(12.f, 0.f, -10.f);
		glVertex3f(2.f, 0.f, -10.f);
	}
	glEnd();
	
	//vertex
	App->scene_intro->VertexArrayCube.DrawVAOCube();
	//Vertex + index
	App->scene_intro->VertexAndIndexCube.DrawIndexCube();

	glLineWidth(1.0f);

}
update_status ModuleSceneIntro::Update(float dt)
{
	return UPDATE_CONTINUE;
}




