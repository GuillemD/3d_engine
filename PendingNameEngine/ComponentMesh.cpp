#include "ComponentMesh.h"



ComponentMesh::ComponentMesh()
{
	MyType = MESH;

}

ComponentMesh::ComponentMesh(GameObject * _gameobject)
{
	if (_gameobject != nullptr) {
		parent = _gameobject;
		MyType = MESH;
	}
	
}


ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::AttachMesh(Mesh * _mesh)
{
	mymesh = _mesh;
}
