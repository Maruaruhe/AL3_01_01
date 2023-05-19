#include "Enemy.h"
#include <assert.h>
#include "Matrix.h"
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model);
	textureHandle_ = TextureManager::Load("Angel.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}
void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	Vector3 velocity(0, 0, 1.0f);
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
}
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}