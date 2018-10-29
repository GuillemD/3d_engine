#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include <string>
#include <vector>
#include "Globals.h"

enum ComponentType;
class Component;


class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent_go, std::string _name);
	~GameObject();

	bool IsActive() const;
	void SetActive(bool _active);
	bool IsStatic()const;
	void SetStatic(bool _static);

	void Draw();

	Component* GetComponent(ComponentType type) const;
	void AddComponent(Component* cp);

public:

	bool staticgo;
	bool active;
	std::string name;
	std::vector<Component*> components;

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	

};
#endif //__GAME_OBJECT_H__
