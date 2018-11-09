#include "Globals.h"
#include "Module.h"
#include "Primitive.h"
#include "GLEW/include/glew.h"
#include "SDL\include\SDL_opengl.h"


// ------------------------------------------------------------
Primitive::Primitive() : transform(transform.identity), color(White), wire(false), axis(false), type(PrimitiveTypes::Primitive_Point)
{
}

// ------------------------------------------------------------
PrimitiveTypes Primitive::GetType() const
{
	return type;
}

// ------------------------------------------------------------
void Primitive::Render() const
{
	glPushMatrix();
	glMultMatrixf((GLfloat*) &transform);
	


	if (axis == true)
	{
		// Draw Axis Grid
		glLineWidth(2.0f);

		glBegin(GL_LINES);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
		glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
		glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
		glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

		glEnd();

		glLineWidth(1.0f);
	}

	glColor3f(color.r, color.g, color.b);

	InnerRender();

	glPopMatrix();
}

// ------------------------------------------------------------
void Primitive::InnerRender() const
{
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	
	glPointSize(1.0f);
}

// ------------------------------------------------------------
void Primitive::SetPos(float x, float y, float z)
{
	transform.Translate(x, y, z);
}

// ------------------------------------------------------------
void Primitive::SetRotation(float angle, const vec &u)
{
	transform.RotateAxisAngle(u, angle);
}

// ------------------------------------------------------------
void Primitive::Scale(float x, float y, float z)
{
	transform.Scale(x, y, z);
}

// CUBE ============================================
PCube::PCube() : Primitive(), size(1.0f, 1.0f, 1.0f)
{
	type = PrimitiveTypes::Primitive_Cube;
}

PCube::PCube(float sizeX, float sizeY, float sizeZ) : Primitive(), size(sizeX, sizeY, sizeZ)
{
	type = PrimitiveTypes::Primitive_Cube;
}

void PCube::InnerRender() const
{
	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-sx, -sy, sz);
	glVertex3f(sx, -sy, sz);
	glVertex3f(sx, sy, sz);
	glVertex3f(-sx, sy, sz);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx, sy, -sz);
	glVertex3f(sx, sy, -sz);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(sx, -sy, sz);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(sx, sy, -sz);
	glVertex3f(sx, sy, sz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx, -sy, sz);
	glVertex3f(-sx, sy, sz);
	glVertex3f(-sx, sy, -sz);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-sx, sy, sz);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, sy, -sz);
	glVertex3f(-sx, sy, -sz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(sx, -sy, sz);
	glVertex3f(-sx, -sy, sz);

	glEnd();
}


// PLANE ==================================================
PPlane::PPlane() : Primitive(), normal(0, 1, 0), constant(1)
{
	type = PrimitiveTypes::Primitive_Plane;
}

PPlane::PPlane(float x, float y, float z, float d) : Primitive(), normal(x, y, z), constant(d)
{
	type = PrimitiveTypes::Primitive_Plane;
}

void PPlane::InnerRender() const
{
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	float d = 10.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}


/*void Mesh::DrawSphere() const
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, sphere_vertices.data());
	glDrawElements(GL_TRIANGLES, (uint)sphere_indices.size(), GL_UNSIGNED_INT, sphere_indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);

}


void Mesh::DefineVerticesAndIndicesForACube(vec _position, float size)
{
	pos = _position;

	glGenBuffers(1, (GLuint*) &(data.id_vertex));
	glGenBuffers(1, (GLuint*) &(data.id_index));

	//type = CUBE_MESH;
	data.num_vertex = 8;
	data.vertex = new vec[data.num_vertex];
	{
		//Front bottom left
		data.vertex[0].x = pos.x;
		data.vertex[0].y = pos.y;
		data.vertex[0].z = pos.z;

		//Front bottom Righ
		data.vertex[1].x = pos.x+size;
		data.vertex[1].y = pos.y;
		data.vertex[1].z = pos.z;

		//Front top left
		data.vertex[2].x = pos.x;
		data.vertex[2].y = pos.y+size;
		data.vertex[2].z = pos.z;

		//Front top Rigth
		data.vertex[3].x = pos.x+size;
		data.vertex[3].y = pos.y+size;
		data.vertex[3].z = pos.z;

		//Back bottom left
		data.vertex[4].x = pos.x;
		data.vertex[4].y = pos.y;
		data.vertex[4].z = pos.z+size;

		//Back bottom Rigth
		data.vertex[5].x = pos.x + size;
		data.vertex[5].y = pos.y;
		data.vertex[5].z = pos.z + size;

		//Back top left
		data.vertex[6].x = pos.x;
		data.vertex[6].y = pos.y + size;
		data.vertex[6].z = pos.z + size;

		//Back top Right
		data.vertex[7].x = pos.x + size;
		data.vertex[7].y = pos.y + size;
		data.vertex[7].z = pos.z + size;

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
	//type = SPHERE_MESH;
	pos = _position;

	float x, y, z, xz;                              // vertex position

	float sectorStep = 2 * PI / secCount;
	float stackStep = PI / stCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;				  // starting from pi/2 to -pi/2
		xz = rad * cosf(stackAngle);						 // r * cos(u)
		y = pos.y + (rad * sinf(stackAngle));            // r * sin(u) + initial pos variation

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coods
		for (int j = 0; j <= secCount; ++j)
		{
			sectorAngle = j * sectorStep;

			// vertex position
			x = pos.x + (xz * cosf(sectorAngle));             // r * cos(u) * cos(v) + initial pos variation
			z = pos.z + (xz * sinf(sectorAngle));             // r * cos(u) * sin(v) + initial pos variation
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

}*/

