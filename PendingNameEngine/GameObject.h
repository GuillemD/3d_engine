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

public:
	bool active;
	std::string name;
	std::vector<Component*> components;

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	

};
#endif //__GAME_OBJECT_H__
