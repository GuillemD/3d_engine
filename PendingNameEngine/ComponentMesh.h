#ifndef __Component__Mesh__
#define __Component__Mesh__

#include "Component.h"
#include "Mesh.h"
class ComponentMesh : public Component {

public:
	ComponentMesh();
	ComponentMesh(GameObject* _gameobject);
	~ComponentMesh();

	void AttachMesh(Mesh* _mesh);
	Mesh* mymesh;

};









#endif // !__Component__Mesh__


