#ifndef __COMPONENT_H__
#define __COMPONENT_H__
#include <string>
#include "SerializationManager.h"
enum ComponentType
{
	MESH = 1,
	MATERIAL,
	TRANSFORMATION,
	CAMERA,
};
class GameObject;
class Component
{
public:

	Component();
	virtual ~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

	virtual void DrawInInspector() {};
	virtual void ChangeTransformEvent() {};

	//virtual void Save(JSON_Value* component) const = 0;
	//virtual void Load(JSON_Value* component) = 0;

	void SetActive(bool _active);
	virtual bool IsActive();

	void SetType(ComponentType ct);
	ComponentType GetType() const;

	void SetOwner(GameObject* own);
	GameObject* GetOwner() const;

	virtual void SetName(const char* n);
	const char* GetName() const;

	
public:
	const char* name;
	ComponentType MyType;
	bool active;
	GameObject* my_go = nullptr;

	uint UUID;

};

#endif //COMPONENT_H__
