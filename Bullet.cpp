#include "Bullet.h"
#include "assert.h"

void Bullet::Initialize(Model* model, const Vector3& position) { 
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Arrow.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Bullet::Update() { 
	worldTransform_.UpdateMatrix();
}

void Bullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}