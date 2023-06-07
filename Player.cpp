#include "Player.h"
#include <ImGuiManager.h>


Player::Player() {

	}
Player::~Player() { 
	 for (Bullet* bullet : bullets_) {
		delete bullet;
	}
}

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
	bullets_.remove_if([] (Bullet * bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
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

	
	if (input_->PushKey(DIK_A)){
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if(input_->PushKey(DIK_D)){
		worldTransform_.rotation_.y += kRotSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	float position[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};


	ImGui::Begin("space desu");

	ImGui::SliderFloat3("Player", position, -30.0f, 30.0f);

	ImGui::End();

	worldTransform_.translation_.x = position[0];
	worldTransform_.translation_.y = position[1];

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX,kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY,kMoveLimitY);

	/*worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);*/

	 worldTransform_.UpdateMatrix();

	 Attack();

	 for (Bullet* bullet : bullets_) {
		bullet->Update();
	 }
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	 for (Bullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	 }
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		Bullet* newBullet = new Bullet();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);

		bullets_.push_back(newBullet);
	}
}