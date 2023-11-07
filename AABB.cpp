#include "AABB.h"



AABB CreateAABB(WorldTransform worldTransform) {
	AABB aabb{};
	for (int i = 0; i < kMaxObject; i++) {
		aabb.min = {1.0f * objectSize.num[0], 1.0f * objectSize.num[1], -1.0f * objectSize.num[2]};
		aabb.max = {-1.0f * objectSize.num[0], -1.0f * objectSize.num[1], 1.0f * objectSize.num[2]};

		aabb.min.num[0] += a.num[0];
		aabb.min.num[1] += a.num[1];
		aabb.min.num[2] += a.num[2];

		aabb.max.num[0] += a.num[0];
		aabb.max.num[1] += a.num[1];
		aabb.max.num[2] += a.num[2];
	}
	return aabb;
}

bool IsCollision(const AABB& a, const AABB& b) {
	if ((a.min.x <= b.max.x && a.max.x >= b.min.x) && (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
	    (a.min.z <= b.max.z && a.max.z >= b.min.z)) {
		return true;
	}
	return false;
}