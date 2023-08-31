#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translation, Vector3 rotation) { 
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;

	viewProjection_.Initialize();
}
	
void RailCamera::Update() {
	/*XINPUT_STATE joyState;
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		worldTransform_.translation_.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		worldTransform_.translation_.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}*/
	//移動　回転
	worldTransform_.translation_.z -= 0.0f;
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