#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::Draw()
{

	glEnableClientState(GL_VERTEX_ARRAY);	
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Mesh::DefineVerticesForACube(vec _position, float size)
{
	position = _position;

	glGenBuffers(1, (GLuint*) &(id_vertices));
	glGenBuffers(1, (GLuint*) &(id_indices));

	type = CUBE_MESH;
	num_vertices = 8;
	vertices = new vec[num_vertices];
	{
		//Front bottom left
		vertices[0].x = position.x;
		vertices[0].y = position.y;
		vertices[0].z = position.z;

		//Front bottom Right
		vertices[1].x = position.x+size;
		vertices[1].y = position.y;
		vertices[1].z = position.z;

		//Front top left
		vertices[2].x = position.x;
		vertices[2].y = position.y+size;
		vertices[2].z = position.z;

		//Front top Rigth
		vertices[3].x = position.x+size;
		vertices[3].y = position.y+size;
		vertices[3].z = position.z;

		//Back bottom left
		vertices[4].x = position.x;
		vertices[4].y = position.y;
		vertices[4].z = position.z+size;

		//Back bottom Rigth
		vertices[5].x = position.x + size;
		vertices[5].y = position.y;
		vertices[5].z = position.z + size;

		//Back top left
		vertices[6].x = position.x;
		vertices[6].y = position.y + size;
		vertices[6].z = position.z + size;

		//Back top Right
		vertices[7].x = position.x + size;
		vertices[7].y = position.y + size;
		vertices[7].z = position.z + size;

	}

	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num_vertices * 3, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	num_indices = 36;
	indices = new uint[num_indices];

	{
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 2;
		indices[4] = 1;
		indices[5] = 3,

		indices[6] = 1;
		indices[7] = 3;
		indices[8] = 5;

		indices[9] = 3;
		indices[10] = 5;
		indices[11] = 7;

		indices[12] = 1;
		indices[13] = 0;
		indices[14] = 4;

		indices[15] = 1;
		indices[16] = 4;
		indices[17] = 5;

		indices[18] = 7;
		indices[19] = 5;
		indices[20] = 4;

		indices[21] = 7;
		indices[22] = 4;
		indices[23] = 6;

		indices[24] = 3;
		indices[25] = 7;
		indices[26] = 2;

		indices[27] = 2;
		indices[28] = 7;
		indices[29] = 6;

		indices[30] = 6;
		indices[31] = 4;
		indices[32] = 0;

		indices[33] = 6;
		indices[34] = 0;
		indices[35] = 2; 
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*num_indices, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	CONSOLELOG("CUBE LOADED BUFFER_ID: %d", id_vertices);
}
