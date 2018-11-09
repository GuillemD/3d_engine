#include "Mesh.h"
#include "Application.h"
#include "Assimp.h"
#include "Globals.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	UnloadVRAMBuffers();
}



void Mesh::UnloadVRAMBuffers()
{
	//delete buffers
	glDeleteBuffers(1, (GLuint*)&this->id_vertex);
	glDeleteBuffers(1, (GLuint*)&this->id_index);
	glDeleteBuffers(1, (GLuint*)&this->id_texture_coords);

	ResetIds();

	if(this->vertex != nullptr) RELEASE_ARRAY(vertex);
	if (this->index != nullptr) RELEASE_ARRAY(index);
	if (this->TexCoords != nullptr) RELEASE_ARRAY(TexCoords);

}

void Mesh::ResetIds()
{
	id_vertex = 0;
	id_index = 0;
	id_texture_coords = 0;
}
