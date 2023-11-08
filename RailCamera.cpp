#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translation, Vector3 rotation) { 
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;

	viewProjection_.Initialize();

	input_ = Input::GetInstance();
}
	
void RailCamera::Update() {
	//移動　回転
	worldTransform_.translation_.z -= 0.0f;

	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_.translation_.x -= 0.2f;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_.translation_.x += 0.2f;
	}

	if (input_->PushKey(DIK_UP)) {
		worldTransform_.translation_.y += 0.2f;
	}

	if (input_->PushKey(DIK_DOWN)) {
		worldTransform_.translation_.y -= 0.2f;
	}

	if (input_->PushKey(DIK_O)) {
		worldTransform_.translation_.z -= 0.2f;
	}

	if (input_->PushKey(DIK_P)) {
		worldTransform_.translation_.z += 0.2f;
	}

	//ワールド行列再計算
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	//imgui
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -30, 100);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, 0, 6);
	ImGui::End();

}