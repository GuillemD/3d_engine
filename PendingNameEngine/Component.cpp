#include "Component.h"
#include "GameObject.h"


Component::Component()
{
	if (my_go != nullptr && my_go->active==true) {
		SetActive(true);
	}

}


Component::~Component()
{
}

void Component::Enable()
{
}

void Component::Update()
{
}

void Component::Disable()
{
}

void Component::SetActive(bool _active)
{
	active = _active;
}

bool Component::IsActive()
{
	return active;
}

ComponentType Component::GetType() const
{

	return MyType;
}

GameObject * Component::GetOwner() const
{
	return my_go;
}
