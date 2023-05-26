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
void Enemy::Update() {/*
	switch (phase_) {
	case Phase::Approach:
	default:
		worldTransform_.UpdateMatrix();
		velocity_ = {0, 0, -0.5f};
		velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
		if (worldTransform_.translation_.z < -10.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		worldTransform_.UpdateMatrix();
		velocity_ = {-0.25f, 0.25f, -0.25f};
		velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
		break;
	}*/
	(this->*spFuncTable[static_cast<size_t>(phase_)])();
	worldTransform_.UpdateMatrix();
	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);
}
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
void Enemy::Approach() {
	velocity_ = {0, 0, -0.25f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.z < -10.0f) {
		phase_ = Phase::Leave;
	}
}
void Enemy::Leave() {
	velocity_ = {-0.25f, 0.25f, -0.25f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
}
void (Enemy::*Enemy::spFuncTable[])() = {
	&Enemy::Approach,
	&Enemy::Leave
};