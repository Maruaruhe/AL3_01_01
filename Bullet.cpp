#include "Bullet.h"
#include "Matrix.h"
#include "Vec3.h"
#include <assert.h>


void Bullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model);
	textureHandle_ = TextureManager::Load("white1x1.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;

	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);
	double dis = std::sqrt(pow(velocity.x, 2) + pow(velocity.z, 2));
	worldTransform_.rotation_.x = std::atan2(-velocity.y, float(dis));

	velocity_ = velocity;
}

void Bullet::Update() { 
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (--deathTimer <= 0) {
		isDead_ = true;
	}
}

void Bullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 Bullet::GetWorldPosition() {
	Vector3 worldPosition;

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];

	return worldPosition;
}

void Bullet::OnCollision() { isDead_ = true; }