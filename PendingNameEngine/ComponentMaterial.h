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

	void DrawInInspector();

public:
	Material* mat = nullptr;
};
#endif // !__COMPONENT_MATERIAL_H__
