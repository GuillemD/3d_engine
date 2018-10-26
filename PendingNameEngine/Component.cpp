#include "Component.h"
#include "GameObject.h"


Component::Component()
{
	
}


Component::~Component()
{
}

void Component::Enable()
{
	active = true;
}

void Component::Update()
{
	
}

void Component::Disable()
{
	active = false;
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
