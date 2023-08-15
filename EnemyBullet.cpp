#include "EnemyBullet.h"
#include "Matrix.h"
#include "Vec3.h"
#include <assert.h>


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	textureHandle_ = TextureManager::Load("bullet.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;

	worldTransform_.scale_.x = 0.5;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;

	worldTransform_.rotation_.y = std::atan2( velocity.x,velocity.z );
	float dis = std::sqrt(pow(velocity.x, 2) + pow(velocity.z, 2));
	worldTransform_.rotation_.x = std::atan2(-velocity.y , dis);
}

void EnemyBullet::Update(Player* player) {
	SetPlayer(player);
	Vector3 toPlayer = Subtract(player->GetWorldPosition(), worldTransform_.translation_);

	Normalize(toPlayer);
	Normalize(velocity_);

	velocity_ = Slerp(velocity_, toPlayer, 1);

	worldTransform_.scale_.x = 0.5;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;

	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float dis = std::sqrt(pow(velocity_.x, 2) + pow(velocity_.z, 2));
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, dis);

	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (--deathTimer <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}