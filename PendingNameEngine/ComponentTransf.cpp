#include "ComponentTransf.h"
#include "GameObject.h"

ComponentTransf::ComponentTransf(GameObject* _gameobject)
{
	if (_gameobject != nullptr) {
		MyType = TRANSFORMATION;
		my_go = _gameobject;
		name = "Component Transformation";
	}
}

ComponentTransf::~ComponentTransf()
{
}
