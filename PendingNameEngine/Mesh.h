#pragma once
#include "Globals.h"
#include "Primitive.h"
#include "MathGeoLib\MathGeoLib.h"
#include "GLEW\include\glew.h"
enum MESH_TYPE {
	CUBE_MESH = 0,
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

	void DrawVAOCube()const;
	void DrawIndexCube() const;
	void DrawSphere() const;


	void DefineVerticesAndIndicesForACube(vec _position, float size);
	void DefineVerticesForACube(vec _position, float size);
	void DefineVerticesForAnArrow(vec _position);
	void DefineVerticesForASphere(vec _position,float rad, uint secCount, uint stCount);


private:
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

	//Sphere
	std::vector<float> sphere_vertices;
	std::vector<uint> sphere_indices;

};

