#pragma once
#include <string>
#include <vector>
#include "Component.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	void SetActive(bool active);

public:
	bool Active;
	std::string Name;
	std::vector<Component*> Components;
	

};

