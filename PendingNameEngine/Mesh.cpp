#include "Mesh.h"
#include "Application.h"
#include "Assimp.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}


void Mesh::DrawMesh() 
{

	glEnableClientState(GL_VERTEX_ARRAY);	
	glBindBuffer(GL_ARRAY_BUFFER, data.id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, data.id_normals);
	glNormalPointer(3, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.id_index);
	glDrawElements(GL_TRIANGLES, data.num_index, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	if (App->renderer3D->v_normals_active)
		DrawVertexNormals();
}

void Mesh::DrawSphere() const
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, sphere_vertices.data());
	glDrawElements(GL_TRIANGLES, (uint)sphere_indices.size(), GL_UNSIGNED_INT, sphere_indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);

}

void Mesh::DrawVertexNormals()
{
	uint normal_length = 3;

	glLineWidth(2.0f);
	glColor3f(0, 0.5f, 1);

	glBegin(GL_LINES);
	for (int i = 0; i < data.num_vertex ; i++)
	{
		glVertex3f(data.vertex->x, data.vertex->y, data.vertex->z);
		glVertex3f(-data.normals->x * normal_length + data.vertex->x, -data.normals->y * normal_length + data.vertex->y, -data.normals->z * normal_length + data.vertex->z);
	}
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1.0f);

}

void Mesh::DefineVerticesAndIndicesForACube(vec _position, float size, vec _color) 
{
	position = _position;

	data.color = _color;

	glGenBuffers(1, (GLuint*) &(data.id_vertex));
	glGenBuffers(1, (GLuint*) &(data.id_index));

	type = CUBE_MESH;
	data.num_vertex = 8;
	data.vertex = new vec[data.num_vertex];
	{
		//Front bottom left
		data.vertex[0].x = position.x;
		data.vertex[0].y = position.y;
		data.vertex[0].z = position.z;

		//Front bottom Right
		data.vertex[1].x = position.x+size;
		data.vertex[1].y = position.y;
		data.vertex[1].z = position.z;

		//Front top left
		data.vertex[2].x = position.x;
		data.vertex[2].y = position.y+size;
		data.vertex[2].z = position.z;

		//Front top Rigth
		data.vertex[3].x = position.x+size;
		data.vertex[3].y = position.y+size;
		data.vertex[3].z = position.z;

		//Back bottom left
		data.vertex[4].x = position.x;
		data.vertex[4].y = position.y;
		data.vertex[4].z = position.z+size;

		//Back bottom Rigth
		data.vertex[5].x = position.x + size;
		data.vertex[5].y = position.y;
		data.vertex[5].z = position.z + size;

		//Back top left
		data.vertex[6].x = position.x;
		data.vertex[6].y = position.y + size;
		data.vertex[6].z = position.z + size;

		//Back top Right
		data.vertex[7].x = position.x + size;
		data.vertex[7].y = position.y + size;
		data.vertex[7].z = position.z + size;

	}

	glBindBuffer(GL_ARRAY_BUFFER, data.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.num_vertex * 3, data.vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	data.num_index = 36;
	data.index = new uint[data.num_index];

	{
		data.index[0] = 0;
		data.index[1] = 1;
		data.index[2] = 2;

		data.index[3] = 2;
		data.index[4] = 1;
		data.index[5] = 3,

		data.index[6] = 1;
		data.index[7] = 5;
		data.index[8] = 3;

		data.index[9] = 3;
		data.index[10] = 5;
		data.index[11] = 7;

		data.index[12] = 5;
		data.index[13] = 4;
		data.index[14] = 7;

		data.index[15] = 7;
		data.index[16] = 4;
		data.index[17] = 6;

		data.index[18] = 4;
		data.index[19] = 0;
		data.index[20] = 6;

		data.index[21] = 6;
		data.index[22] = 0;
		data.index[23] = 2;

		data.index[24] = 2;
		data.index[25] = 3;
		data.index[26] = 6;

		data.index[27] = 6;
		data.index[28] = 3;
		data.index[29] = 7;

		data.index[30] = 4;
		data.index[31] = 5;
		data.index[32] = 0;

		data.index[33] = 0;
		data.index[34] = 5;
		data.index[35] = 1; 
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*data.num_index, data.index, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CONSOLELOG("CUBE LOADED BUFFER_ID: %d", data.id_vertex);
}


void Mesh::DefineVerticesForASphere(vec _position, float rad, uint secCount, uint stCount)
{
	type = SPHERE_MESH;
	position = _position;

	float x, y, z, xz;                              // vertex position

	float sectorStep = 2 * PI / secCount;
	float stackStep = PI / stCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;				  // starting from pi/2 to -pi/2
		xz = rad * cosf(stackAngle);						 // r * cos(u)
		y = position.y + (rad * sinf(stackAngle));            // r * sin(u) + initial pos variation

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coods
		for (int j = 0; j <= secCount; ++j)
		{
			sectorAngle = j * sectorStep;

			// vertex position
			x = position.x + (xz * cosf(sectorAngle));             // r * cos(u) * cos(v) + initial pos variation
			z = position.z + (xz * sinf(sectorAngle));             // r * cos(u) * sin(v) + initial pos variation
			sphere_vertices.push_back(x);
			sphere_vertices.push_back(y);
			sphere_vertices.push_back(z);

		}
	}

	// indices
	uint k1, k2;
	for (int i = 0; i < stCount; ++i)
	{
		k1 = i * (secCount + 1);     // beginning of current stack
		k2 = k1 + secCount + 1;      // beginning of next stack

		for (int j = 0; j < secCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding 1st and last stacks
			if (i != 0)
			{
				sphere_indices.push_back(k1);
				sphere_indices.push_back(k2);
				sphere_indices.push_back(k1 + 1);
			}

			if (i != (stCount - 1))
			{
				sphere_indices.push_back(k1 + 1);
				sphere_indices.push_back(k2);
				sphere_indices.push_back(k2+1);
			}

		}
	}

}

