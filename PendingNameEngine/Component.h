#ifndef __COMPONENT_H__
#define __COMPONENT_H__

enum ComponentType
{
	MESH = 1,
	TEXTURE
};
class GameObject;
class Component
{
public:

	Component();
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

	void SetActive(bool _active);
	bool IsActive();
	ComponentType GetType() const;
	GameObject* GetOwner() const;


public:

	ComponentType MyType;
	bool active;
	GameObject* my_go;

};

#endif //COMPONENT_H__
