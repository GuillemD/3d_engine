#ifndef __DEBUGDRAW_H__
#define __DEBUGDRAW_H__

#include "Globals.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Color.h"

void BeginDebugDraw();
void EndDebugDraw();


void DebugDraw(const AABB& aabb, Color color = White, const float4x4& transform = float4x4::identity);

void CubeDirectDraw(const float3 * corners, Color color);

void PlaneDirectDraw(const float4x4 & transform);

#endif //__DEBUGDRAW_H__
