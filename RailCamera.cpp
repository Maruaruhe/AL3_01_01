#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translation, Vector3 rotation) { 
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;

	viewProjection_.Initialize();
}
	
void RailCamera::Update() {
	//移動　回転
	worldTransform_.translation_.z += 0.1;
	//ワールド行列再計算
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	//imgui
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -30, 100);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -30, 100);
	ImGui::End();

}