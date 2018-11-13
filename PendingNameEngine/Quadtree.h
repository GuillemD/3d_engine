#ifndef __Quatree__
#define __Quatree__
#include "MathGeoLib/MathGeoLib.h"
#include "GameObject.h"
#include <vector>
class Quadtree
{
public:
	Quadtree(AABB limits);
	~Quadtree();
	void Clear();
	void Insert(GameObject* _go);
	void Remove(GameObject* _go);
	void Intersect(std::vector<GameObject*>& _go, )

	
};





#endif // !__Quatree__



