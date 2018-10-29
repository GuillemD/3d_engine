#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"
class Material;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial();
	ComponentMaterial(GameObject* _gameobject);
	~ComponentMaterial();

public:
	Material* mat;
};
#endif // !__COMPONENT_MATERIAL_H__
