#include "GameObject.h"
#include "Component.h"
#include "OpenGL.h"



GameObject::GameObject()
{
	parent = nullptr;
	active = true;
}

GameObject::GameObject(GameObject * parent_go, std::string _name)
{
}



GameObject::~GameObject()
{
}

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::SetActive(bool _active)
{
	if (active != _active)
	{
		active = _active;
	}
}
