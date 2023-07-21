#include "RailCamera.h"

void RailCamera::Initialize(WorldTransform wt) { 
	worldTransform_.translation_ = wt.translation_;
	worldTransform_.rotation_ = wt.rotation_;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	viewProjection_.Initialize();
}
	
void RailCamera::Update() {
	//移動　回転
	worldTransform_.translation_.z -= 5;
	//ワールド行列再計算
	/*worldTransform_.UpdateMatrix();*/
	//
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	//imgui
	float translation[3] = {
	    translation[0] = worldTransform_.translation_.x,
	    translation[1] = worldTransform_.translation_.y,
	    translation[2] = worldTransform_.translation_.z,
	};

	float rotation[3] = {
	    rotation[0] = worldTransform_.rotation_.x,
	    rotation[1] = worldTransform_.rotation_.y,
	    rotation[2] = worldTransform_.rotation_.z,
	};

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", translation, -30, 100);
	ImGui::SliderFloat3("rotation", rotation, -30, 100);
	ImGui::End();

}