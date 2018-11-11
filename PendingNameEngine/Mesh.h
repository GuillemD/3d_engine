#ifndef _MESH_H_
#define _MESH_H_

#include "Globals.h"
#include "MathGeoLib\MathGeoLib.h"
#include "OpenGL.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

	void ResetIds();
	void UnloadVRAMBuffers();

public:
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint num_faces = 0;

	float* TexCoords = nullptr;
	uint id_texture_coords = 0;
	uint num_texture_coords = 0;

	AABB outside_box;

};


#endif // !_MESH_H_

