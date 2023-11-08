#include "Player.h"
#include <ImGuiManager.h>


Player::Player() {

}
Player::~Player() { 
	 for (Bullet* bullet : bullets_) {
		delete bullet;
	}
	 delete sprite2DReticle_;
}

void Player::Initialize(
    Model* model, Model* reticleModel, uint32_t textureHandle, Vector3 playerPosition) {
	model_ = Model::Create();
	assert(model);

	reticleModel_ = Model::Create();
	assert(reticleModel_);

	model_ = model;
	reticleModel_ = reticleModel;
	textureHandle_ = textureHandle;
	uint32_t textureReticle = TextureManager::Load("reticle.png");
	sprite2DReticle_ = Sprite::Create(textureReticle, {640, 360}, {1, 1, 1, 1}, {0.5, 0.5});

	input_ = Input::GetInstance();



	worldTransform_.Initialize();
	//worldTransform_.translation_= Add(worldTransform_.rotation_, playerPosition);
	worldTransform_.translation_= playerPosition;
	worldTransform3DReticle_.Initialize();
}

void Player::Update(ViewProjection viewProjection) { 
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	bullets_.remove_if([] (Bullet * bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	//move
	if (input_->PushKey(DIK_A)) {
		if (!isCollision) {
			move.x -= kCharacterSpeed;
		} else {
			move.x += kCharacterSpeed;
		}
	}
	if (input_->PushKey(DIK_D)) {
		if (!isCollision) {
			move.x += kCharacterSpeed;
		} else {
			move.x -= kCharacterSpeed;
		}
	}

	if (input_->PushKey(DIK_E)) {
		if (!isCollision) {
			move.z += kCharacterSpeed;
		} else {
			move.z -= kCharacterSpeed;
		}
	}
	if (input_->PushKey(DIK_Q)) {
		if (!isCollision) {
			move.z -= kCharacterSpeed;
		} else {
			move.z += kCharacterSpeed;
		}
	}

	if (input_->PushKey(DIK_W)) {
		if (!isCollision) {
			move.y += kCharacterSpeed;
		} else {
			move.y -= kCharacterSpeed;
		}
	}
	if (input_->PushKey(DIK_S)) {
		if (!isCollision) {
			move.y -= kCharacterSpeed;
		} else {
			move.y += kCharacterSpeed;
		}
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	ImGui::Begin("space desu");
	ImGui::SliderFloat3("Playerworld", &worldTransform_.translation_.x, -30.0f, 30.0f);
	ImGui::SliderFloat3("Playerscale", &worldTransform_.scale_.x, 0.0f, 10.0f);

	ImGui::End();

	//worldTransform_.translation_.x = position[0];
	//worldTransform_.translation_.y = position[1];

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX,kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY,kMoveLimitY);

	/*worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);*/

	 worldTransform_.UpdateMatrix();

	 const float kDistancePlayerTo3DReticle = 50.0f;

	 Vector3 offset = {0, 0, 1.0f};
	 
	 offset = TransformNormal(offset, worldTransform_.matWorld_);
	 //offset = MultiplyVectorMatrix(offset, worldTransform_.matWorld_);
	 offset.x = Normalize(offset).x * kDistancePlayerTo3DReticle;
	 offset.y = Normalize(offset).y * kDistancePlayerTo3DReticle;
	 offset.z = Normalize(offset).z * kDistancePlayerTo3DReticle;

	 worldTransform3DReticle_.translation_.x = offset.x + worldTransform_.translation_.x;
	 worldTransform3DReticle_.translation_.y = offset.y + worldTransform_.translation_.y;
	 worldTransform3DReticle_.translation_.z = offset.z + worldTransform_.translation_.z;

	 worldTransform3DReticle_.UpdateMatrix();
	 worldTransform3DReticle_.TransferMatrix();

	 Vector3 positionReticle = worldTransform3DReticle_.translation_;
	 Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	 Matrix4x4 matViewProjectionViewport = Multiply(viewProjection.matView , Multiply(viewProjection.matProjection , matViewport));
	 //Matrix4x4 matViewProjectionViewport = Multiply(viewProjection.matView , Multiply(viewProjection.matProjection , matViewport));
	 positionReticle = Transform(positionReticle, matViewProjectionViewport);
	 sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));


	 Attack();
	 OnCollision();

	 for (Bullet* bullet : bullets_) {
		bullet->Update();
	 }
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	 //reticleModel_->Draw(worldTransform3DReticle_, viewProjection_, textureHandle_);
	 for (Bullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	 }
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		//const float kBulletSpeed = 1.0f;
		/*Vector3 velocity(0, 0, kBulletSpeed);
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);*/
		Vector3 velocity = Subtract(worldTransform3DReticle_.translation_, worldTransform_.translation_);
		velocity = Normalize(velocity);
		Bullet* newBullet = new Bullet();
		//newBullet->Initialize(model_, worldTransform_.translation_,velocity);
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() { 
	Vector3 worldPosition;

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];

	return worldPosition;
	}

void Player::OnCollision() {
	if (isCollision){
		ImGui::SliderFloat3("Playerrotation", &worldTransform_.rotation_.x, 0.0f, 10.0f);
	} else {
	
	}
}

void Player::SetParent(const WorldTransform* parent) { 
	worldTransform_.parent_ = parent;
	}

void Player::DrawUI() { 
	sprite2DReticle_->Draw();
}