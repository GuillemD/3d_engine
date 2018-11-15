#ifndef __Component__Mesh__
#define __Component__Mesh__

#include "Component.h"
#include "Mesh.h"

class ComponentMesh : public Component {

public:
	ComponentMesh(GameObject* _gameobject);
	~ComponentMesh();

	void DrawInInspector();

	void AttachMesh(Mesh* _mesh);
	void UpdateBoundingBox();

	void TransformMesh(float4x4* _transf);
	Mesh* my_mesh;

};

#endif // !__Component__Mesh__


