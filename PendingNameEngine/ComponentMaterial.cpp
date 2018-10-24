#include "ComponentMaterial.h"
#include "GameObject.h"


ComponentMaterial::ComponentMaterial(GameObject* _gameobject)
{
	if (_gameobject != nullptr) {
		my_go = _gameobject;
		MyType = MATERIAL;
		name = "Material Component";
	}
}
ComponentMaterial::~ComponentMaterial()
{
}
