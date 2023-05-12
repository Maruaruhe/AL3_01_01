#include "Player.h"
#include <ImGuiManager.h>

void Player::Initialize(Model* model, uint32_t textureHandle) { 
	model_ = Model::Create();
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
}

void Player::Update() { 
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	float position[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	/*Matrix4x4 scaleMatrix = MakeScaleMatrix(worldTransform_.scale_);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(worldTransform_.rotation_.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(worldTransform_.rotation_.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(worldTransform_.rotation_.z);

	Matrix4x4 rotateXYZMatrix = Multiply(rotateZMatrix, Multiply(rotateXMatrix, rotateYMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(worldTransform_.translation_);

	worldTransform_.matWorld_ = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));*/


	ImGui::Begin("wa");

	ImGui::SliderFloat3("Player", position, -30.0f, 30.0f);

	ImGui::End();

	worldTransform_.translation_.x = position[0];
	worldTransform_.translation_.y = position[1];

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX,kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY,kMoveLimitY);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	 worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}