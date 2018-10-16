#pragma once
#include "GameObject.h"
class Component
{
public:
	Component();
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();


public:

	ComponentType MyType;
	bool Active;
	GameObject* Parent;

};

enum ComponentType
{
	MESH = 1,
	TEXTURE
};
