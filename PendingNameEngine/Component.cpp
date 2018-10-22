#include "Component.h"



Component::Component()
{
	if (Parent != nullptr && Parent->Active==true) {
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

void Component::SetActive(bool active)
{
	Active = active;
}

bool Component::IsActive()
{
	return Active;
}

Component::ComponentType Component::GetType()
{


	return MyType;
}

GameObject * Component::GetParent()
{
	return Parent;
}
