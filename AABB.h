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
struct OBB {
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};

struct Direction {
	bool front;
	bool back;
	bool right;
	bool left;
	bool top;
	bool bot;
};


AABB CreateAABB(WorldTransform worldTransform);
bool IsCollision(const AABB& a, const AABB& b);
Direction CheckDirection(const AABB& a, const AABB& b);