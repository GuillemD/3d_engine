#ifndef __Quatree__
#define __Quatree__
#include "MathGeoLib/MathGeoLib.h"
#include "GameObject.h"
#include <vector>
class Quadtree
{
public:
	Quadtree();
	Quadtree(AABB _qtbb, int _currentsubdivisions);
	~Quadtree();
	void Clear();
	void Insert(GameObject* _go);
	void Remove(GameObject* _go);
	void SubDivide();
	void CheckIntersections(std::vector<GameObject*>& _go, AABB* _goboundingbox);
	void RenderQuadTree();

public:
	AABB * quadtreeboundingbox;
	int my_subdivision;
	std::vector<Quadtree*> childs;
	std::vector<GameObject*> my_objects;
	int maxcapacity= 1;
};





#endif // !__Quatree__



