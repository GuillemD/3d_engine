#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <vector>
#include "Globals.h"
#include "MathGeoLib/MathGeoLib.h"

enum ComponentType;
class Component;
class Material;
class Mesh;
class ComponentTransf;
class ComponentMesh;


class GameObject
{
public:

	GameObject(std::string _name, GameObject* parent_go = nullptr, bool _active = true);
	virtual ~GameObject();

	void Update();
	void OnTransformEvent();

	bool IsActive() const;
	void SetActive(bool _active);
	bool IsStatic() const;
	void SetStatic(bool _static);
	bool IsSelected() const;
	void SetSelected(bool _selected);

	void SetName(const std::string& n);
	std::string GetName() const;


	void Draw();
	void DrawInHierarchy();
	void DrawInInspector();

	void RenderBoundingBox();

	Component* GetComponentByType(ComponentType type) const;
	void AddComponent(Component* cp);
	std::vector<Component*> GetComponents() const;

	ComponentTransf* GetComponentTransform();
	ComponentMesh* GetComponentMesh();

	bool HasComponentMesh();
	bool HasComponentTransform();

	GameObject* GetParent() const;
	void SetParent(GameObject* _parent);

	GameObject* CreateChild(std::string _name);
	void PushChild(GameObject* _child);
	std::vector<GameObject*> GetChildren() const;

public:

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	bool staticgo = false;
	bool active = true;
	bool selected = false;
	std::string name;
	std::vector<Component*> components;
	math::AABB boundingbox;

};
#endif //__GAME_OBJECT_H__
