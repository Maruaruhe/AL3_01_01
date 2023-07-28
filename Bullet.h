#pragma once
#include "Model.h"
#include "Vector3.h"
#include <WorldTransform.h>

class Bullet {
public:
	//Bullet();
	//~Bullet();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	bool isDead() const { return isDead_; }

	void OnCollision();

	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	static const int32_t kLifeTime = 60 * 2;
	int32_t deathTimer = kLifeTime;
	bool isDead_ = false;
};