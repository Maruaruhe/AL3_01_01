#pragma once
#include "Model.h"
#include "Vec3.h"
#include <WorldTransform.h>
#include "Player.h"

class EnemyBullet {
public:
	// Bullet();
	//~Bullet();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update(Player* player);

	void Draw(const ViewProjection& viewProjection);

	bool isDead() const { return isDead_; }

	void SetPlayer(Player* player) { player_ = player; }

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer = kLifeTime;
	bool isDead_ = false;

	Player* player_;
};