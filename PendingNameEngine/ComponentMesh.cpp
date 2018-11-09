#include "ComponentMesh.h"
#include "GameObject.h"
#include "ImGui/imgui.h"



ComponentMesh::ComponentMesh(GameObject * _gameobject)
{
	if (_gameobject != nullptr) {
		my_go = _gameobject;
		MyType = MESH;
		name = "Mesh Component";
	}
	
}


ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::DrawInInspector()
{
	if (my_mesh != nullptr)
	{
		if (ImGui::CollapsingHeader("Component Mesh"))
		{
			ImGui::Text("Num Vertices: %d", my_mesh->num_vertex);
			ImGui::Text("Num Index: %d", my_mesh->num_index);
			ImGui::Text("Num TexCoords: %d", my_mesh->num_texture_coords);
		}
		
	}
	
}

void ComponentMesh::AttachMesh(Mesh * _mesh)
{
	my_mesh = _mesh;
}
