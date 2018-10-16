#pragma once
#include <string>
#include <vector>
#include "Component.h"
class GameObject
{
public:
	GameObject();
	~GameObject();


public:
	bool Active;
	std::string Name;
	std::vector<Component*> Components;


};

