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

	float* TexCoords = nullptr;
	uint id_texture_coords = 0;
	uint num_texture_coords = 0;

	uint texture_width = 0;
	uint texture_heigth = 0;

	void ResetIds();

};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void DrawMesh();
	void DrawSphere() const;

	void DefineVerticesAndIndicesForACube(vec _position, float size);
	void DefineVerticesForASphere(vec _position,float rad, uint secCount, uint stCount);

	AABB outside_box;
	VertexData data;
	float3 pos;
	uint id_texture;;

	void UnloadVRAMBuffers();
	
private:

	MESH_TYPE type;

	//Sphere
	std::vector<float> sphere_vertices;
	std::vector<uint> sphere_indices;

	

};

