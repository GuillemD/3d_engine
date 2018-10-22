#pragma once
#include "GameObject.h"
class Component
{
public:

	enum ComponentType
	{
		MESH = 1,
		TEXTURE
	};


	Component();
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

	void SetActive(bool active);
	bool IsActive();
	Component::ComponentType GetType();
	GameObject* GetParent();


public:

	Component::ComponentType MyType;
	bool Active;
	GameObject* Parent;

};


