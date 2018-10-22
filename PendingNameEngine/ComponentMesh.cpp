#include "ComponentMesh.h"
#include "GameObject.h"



ComponentMesh::ComponentMesh(GameObject * _gameobject)
{
	if (_gameobject != nullptr) {
		my_go = _gameobject;
		MyType = MESH;
	}
	
}


ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::AttachMesh(Mesh * _mesh)
{
	my_mesh = _mesh;
}
