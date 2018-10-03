#pragma once
#include "Globals.h"
#include "Primitive.h"
#include "MathGeoLib\MathGeoLib.h"
#include "OpenGL.h"
enum MESH_TYPE {
	CUBE_MESH = 0,
	SPHERE_MESH,
	CYLINDER_MESH,
	ARROW_MESH,
	CAPSULE_MESH,
	FRUSTUM_MESH
};
struct VertexData {
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	vec* vertex = nullptr;
	uint id_normals = 0; //texture in VRAM
	uint num_normals = 0;
	vec* normals = nullptr;
};
class Mesh
{
public:
	Mesh();
	~Mesh();

	void DrawMesh() const;
	void DrawSphere() const;


	void DefineVerticesAndIndicesForACube(vec _position, float size);
	void DefineVerticesForAnArrow(vec _position);
	void DefineVerticesForASphere(vec _position,float rad, uint secCount, uint stCount);
	//void DefineVerticesForACylinder(vec _position, float rad, float length, uint slices);


	VertexData data;
private:
	vec color;
	MESH_TYPE type;

	vec position = vec(0.f, 0.f, 0.f);
	Quat rotation = Quat::identity;	
	vec scale = vec(1.f, 1.f, 1.f);


	//Sphere
	std::vector<float> sphere_vertices;
	std::vector<uint> sphere_indices;

};

