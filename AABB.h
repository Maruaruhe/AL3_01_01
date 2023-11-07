#pragma once
#include "Matrix.h"
#include "Vec3.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include <WorldTransform.h>

struct AABB {
	Vector3 min;
	Vector3 max;
};


AABB CreateAABB(WorldTransform worldTransform);
bool IsCollision(const AABB& a, const AABB& b);