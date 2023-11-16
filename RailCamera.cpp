#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translation, Vector3 rotation) { 
	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;

	viewProjection_.Initialize();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.matProjection = MakePerspectiveFovMatrix(viewProjection_.fovAngleY, viewProjection_.aspectRatio, viewProjection_.nearZ,viewProjection_.farZ);

	input_ = Input::GetInstance();
}
	
void RailCamera::Update() {
	//移動　回転
	worldTransform_.translation_.z -= 0.0f;

	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_.rotation_.y -= 0.02f;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_.rotation_.y += 0.02f;
	}

	if (input_->PushKey(DIK_UP)) {
		worldTransform_.rotation_.x -= 0.02f;
	}

	if (input_->PushKey(DIK_DOWN)) {
		worldTransform_.rotation_.x += 0.02f;
	}

	if (input_->PushKey(DIK_O)) {
		worldTransform_.translation_.z -= 0.2f;
	}

	if (input_->PushKey(DIK_P)) {
		worldTransform_.translation_.z += 0.2f;
	}

	//ワールド行列再計算
	//worldTransform_.UpdateMatrix();
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//worldTransform_.matWorld_ = MakeRotateXYZMatrix(worldTransform_.rotation_);
	//worldTransform_.TransferMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.matProjection = MakePerspectiveFovMatrix(viewProjection_.fovAngleY, viewProjection_.aspectRatio, viewProjection_.nearZ, viewProjection_.farZ);

	//imgui
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -30, 100);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, 0, 6);
	ImGui::End();

}