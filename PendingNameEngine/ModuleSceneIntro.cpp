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
	
	VertexAndIndexCube.DefineVerticesAndIndicesForACube(vec(7.f, -1.f, -1.f), 2);
	VertexArrayCube.DefineVerticesForACube(vec(3.f, -1.f, -1.f), 2);
	Sphere.DefineVerticesForASphere(vec(0.f, 6.f, 0.f), 2, 16, 16);
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
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	{
		//Front face
		glVertex3f(-1.f, -1.f, 1.f); //0
		glVertex3f(1.f, -1.f, 1.f); //1
		glVertex3f(-1.f, 1.f, 1.f); //2

		glVertex3f(-1.f, 1.f, 1.f); //2
		glVertex3f(1.f, -1.f, 1.f); //1
		glVertex3f(1.f, 1.f, 1.f); //3

		//Right face
		glVertex3f(1.f, -1.f, 1.f); //1
		glVertex3f(1.f, -1.f, -1.f); //4
		glVertex3f(1.f, 1.f, 1.f); //3

		glVertex3f(1.f, 1.f, 1.f); //3
		glVertex3f(1.f, -1.f, -1.f); //4
		glVertex3f(1.f, 1.f, -1.f); //6

		//Top face
		glVertex3f(-1.f, 1.f, 1.f); //2
		glVertex3f(1.f, 1.f, 1.f); //3
		glVertex3f(-1.f, 1.f, -1.f); //7

		glVertex3f(-1.f, 1.f, -1.f); //7
		glVertex3f(1.f, 1.f, 1.f); //3
		glVertex3f(1.f, 1.f, -1.f); //6

		//Back face
		glVertex3f(1.f, -1.f, -1.f); //4
		glVertex3f(-1.f, -1.f, -1.f); //5
		glVertex3f(1.f, 1.f, -1.f); //6

		glVertex3f(1.f, 1.f, -1.f); //6
		glVertex3f(-1.f, -1.f, -1.f); //5
		glVertex3f(-1.f, 1.f, -1.f); //7

		//Left face
		glVertex3f(-1.f, -1.f, -1.f); //5
		glVertex3f(-1.f, -1.f, 1.f); //0
		glVertex3f(-1.f, 1.f, -1.f); //7

		glVertex3f(-1.f, 1.f, -1.f); //7
		glVertex3f(-1.f, -1.f, 1.f); //0
		glVertex3f(-1.f, 1.f, 1.f); //2 

		//Bottom face
		glVertex3f(-1.f, -1.f, -1.f); //5
		glVertex3f(1.f, -1.f, -1.f); //4
		glVertex3f(-1.f, -1.f, 1.f); //0

		glVertex3f(-1.f, -1.f, 1.f); //0
		glVertex3f(1.f, -1.f, -1.f); //4
		glVertex3f(1.f, -1.f, 1.f); //1
	}
	glEnd();
	
	glColor3f(0.0, 1.0, 0.0);
	//vertex
	App->scene_intro->VertexArrayCube.DrawVAOCube();

	//Vertex + index
	glColor3f(0.0, 0.0, 1.0);
	App->scene_intro->VertexAndIndexCube.DrawIndexCube();
	glColor3f(1.0, 1.0, 1.0);
	//Sphere
	App->scene_intro->Sphere.DrawSphere();	

	glLineWidth(1.0f);

}

update_status ModuleSceneIntro::Update(float dt)
{

	angle += 0.5f;

	if (angle >= 360.0f)
		angle = 0.0f;
	return UPDATE_CONTINUE;
}




