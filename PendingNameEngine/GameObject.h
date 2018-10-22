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
	~GameObject();

	void SetActive(bool _active);

public:
	bool active;
	std::string name;
	std::vector<Component*> components;
	

};
#endif //__GAME_OBJECT_H__
