#pragma once
#include "Vector3.h"

class Collider {
public:

	virtual void OnCollision() = 0;

	virtual Vector3 GetWorldPosition() = 0;

	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }

private:
	// 半径
	float radius_ = 2;
};