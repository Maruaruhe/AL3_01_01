﻿#include "Bullet.h"
#include "Matrix.h"
#include "Vec3.h"
#include <assert.h>


void Bullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) { 
	assert(model);
	textureHandle_ = TextureManager::Load("Arrow.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
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