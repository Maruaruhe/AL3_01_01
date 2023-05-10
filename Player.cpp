#include "Player.h"
void Player::Initialize(Model* model, uint32_t textureHandle) { 
	model_ = Model::Create();
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
}

void Player::Update() { 
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}