#include "Component.h"
#include "GameObject.h"



Component::Component()
{
	active = true;
	//UUID = generateUID();
	
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

void Component::SetType(ComponentType ct)
{
	MyType = ct;
}

ComponentType Component::GetType() const
{

	return MyType;
}

void Component::SetOwner(GameObject * own)
{
	my_go = own;
}

GameObject * Component::GetOwner() const
{
	return my_go;
}

void Component::SetName(const char * n)
{
	name = n;
}

const char * Component::GetName() const
{
	return name;
}
