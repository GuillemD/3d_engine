#pragma once
#include "Globals.h"
#include "MathGeoLib\MathGeoLib.h"
#include "GLEW\include\glew.h"
enum MESH_TYPE {
	CUBE_MESH = 0,
	PLANE_MESH,
	SPHERE_MESH,
	ARROW_MESH,
	CAPSULE_MESH,
	FRUSTUM_MESH
};
class Mesh
{
public:
	Mesh();
	~Mesh();

	void DrawVAOCube();
	void DrawIndexCube();
	void DefineVerticesAndIndicesForACube(vec _position, float size);
	void DefineVerticesForACube(vec _position, float size);
	void DefineVerticesForAPlane(vec _position);
	void DefineVerticesForAnArrow(vec _position);
	void DefineVerticesForASphere(float radius, uint rings, uint sectors);

public:
	vec color;
	MESH_TYPE type;

	vec position = vec(0.f, 0.f, 0.f);
	Quat rotation = Quat::identity;	
	vec scale = vec(1.f, 1.f, 1.f);

	vec* vertices;
	vec* unique_vertices;
	uint* indices;

	uint num_vertices;
	uint num_unique_vertices;
	uint num_indices;

	uint id_vertices;
	uint id_unique_vertices;
	uint id_indices;

};

