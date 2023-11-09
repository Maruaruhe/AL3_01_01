#include "AABB.h"



AABB CreateAABB(WorldTransform worldTransform) {
	AABB aabb{};
	aabb.min = {
	    -1.0f * worldTransform.scale_.x, -1.0f * worldTransform.scale_.y,
	    -1.0f * worldTransform.scale_.z};
	aabb.max = {
	    1.0f * worldTransform.scale_.x, 1.0f * worldTransform.scale_.y,
	    1.0f * worldTransform.scale_.z};

	aabb.min.x += worldTransform.translation_.x;
	aabb.min.y += worldTransform.translation_.y;
	aabb.min.z += worldTransform.translation_.z;

	aabb.max.x += worldTransform.translation_.x;
	aabb.max.y += worldTransform.translation_.y;
	aabb.max.z += worldTransform.translation_.z;

	return aabb;
}

bool IsCollision(const AABB& a, const AABB& b) {
	if ((a.min.x < b.max.x && a.max.x > b.min.x) && (a.min.y < b.max.y && a.max.y > b.min.y) &&
	    (a.min.z < b.max.z && a.max.z > b.min.z)) {
		return true;
	}
	return false;
}

Direction CheckDirection(const AABB& a, const AABB& b) { 
	Direction direction{};
	//
	if (a.min.x >= b.max.x) {
		direction.left = true;

		direction.right = false;
	}
	if (a.max.x <= b.min.x) {
		direction.right = true;

		direction.left = false;
	}
	//
	if (a.min.z >= b.min.z) {
		direction.back = true;

		direction.front = false;
	}
	if (a.max.z <= b.min.z) {
		direction.front = true;

		direction.back = false;
	}
	//縦
	if (a.min.y >= b.max.y) {
		direction.top = true;

		direction.bot = false;
	}
	if (a.max.y <= b.min.y) {
		direction.bot = true;

		direction.top = false;
	}
	return direction;
}