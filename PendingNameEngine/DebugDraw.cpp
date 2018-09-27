#include "DebugDraw.h"
#include "GLEW/include/glew.h"
#include "SDL/include/SDL_opengl.h"

void BeginDebugDraw()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);
	glColor4f(1.f, 1.f, 1.f, 1.f);
}

void EndDebugDraw()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}



