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
	worldTransform_.translation_= Add(worldTransform_.rotation_, playerPosition);
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

	 worldTransform_.UpdateMatrix();

	 //3DReticle
	 const float kDistancePlayerTo3DReticle = 50.0f;

	 Vector3 offset = {0, 0, 1.0f};
	 
	 offset = TransformNormal(offset, worldTransform_.matWorld_);
	 offset.x = Normalize(offset).x * kDistancePlayerTo3DReticle;
	 offset.y = Normalize(offset).y * kDistancePlayerTo3DReticle;
	 offset.z = Normalize(offset).z * kDistancePlayerTo3DReticle;

	 worldTransform3DReticle_.translation_.x = offset.x + worldTransform_.translation_.x;
	 worldTransform3DReticle_.translation_.y = offset.y + worldTransform_.translation_.y;
	 worldTransform3DReticle_.translation_.z = offset.z + worldTransform_.translation_.z;

	 worldTransform3DReticle_.UpdateMatrix();
	 worldTransform3DReticle_.TransferMatrix();

	 //2DReticle
	 Vector3 positionReticle = worldTransform3DReticle_.translation_;
	 Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	 Matrix4x4 matViewProjectionViewport = Multiply(viewProjection.matView , Multiply(viewProjection.matProjection , matViewport));
	 positionReticle = Transform(positionReticle, matViewProjectionViewport);
	 sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
	 //2D標準
	 POINT mousePosition;
	 GetCursorPos(&mousePosition);

	 HWND hwnd = WinApp::GetInstance()->GetHwnd();
	 ScreenToClient(hwnd, &mousePosition);
	 sprite2DReticle_->SetPosition(Vector2(mousePosition.x, mousePosition.y));
	 //
	 Matrix4x4 matVPV = Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
	 Matrix4x4 matInverseVPV = Inverse(matVPV);

	 Vector3 posNear = Vector3(mousePosition.x, mousePosition.y, 0);
	 Vector3 posFar = Vector3(mousePosition.x, mousePosition.y, 1);
	 posNear = Transform(posNear, matInverseVPV);
	 posFar = Transform(posFar, matInverseVPV);

	 Vector3 mouseDirection = Subtract(posFar, posNear);
	 mouseDirection = Normalize(mouseDirection);

	 const float kDistanceTestObject = 50.0f;
	 worldTransform3DReticle_.translation_.x = posNear.x + mouseDirection.x + kDistanceTestObject;
	 worldTransform3DReticle_.translation_.y = posNear.y + mouseDirection.y + kDistanceTestObject;
	 worldTransform3DReticle_.translation_.z = posNear.z + mouseDirection.z + kDistanceTestObject;

	 worldTransform3DReticle_.UpdateMatrix();
	 worldTransform3DReticle_.TransferMatrix();

	 ImGui::Begin("Player");
	 ImGui::Text(
	     "2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	 ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	 ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	 ImGui::Text(
	     "3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x,
	     worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	 ImGui::End();
	 //
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
		//Vector3 velocity(0, 0, kBulletSpeed);
		//velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		Vector3 velocity =
		    Subtract(worldTransform3DReticle_.translation_, worldTransform_.translation_);
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

}

void Player::SetParent(const WorldTransform* parent) { 
	worldTransform_.parent_ = parent;
	}

WorldTransform Player::Create3DReticle() {
	const float kDistancePlayerTo3DReticle = 50.0f;

	Vector3 offset = {0, 0, 1.0f};

	offset = TransformNormal(offset, worldTransform_.matWorld_);
	offset.x = Normalize(offset).x * kDistancePlayerTo3DReticle;
	offset.y = Normalize(offset).y * kDistancePlayerTo3DReticle;
	offset.z = Normalize(offset).z * kDistancePlayerTo3DReticle;

	WorldTransform worldTransform3DReticle;
	worldTransform3DReticle.translation_.x = offset.x + worldTransform_.translation_.x;
	worldTransform3DReticle.translation_.y = offset.y + worldTransform_.translation_.y;
	worldTransform3DReticle.translation_.z = offset.z + worldTransform_.translation_.z;

	worldTransform3DReticle.UpdateMatrix();
	worldTransform3DReticle.TransferMatrix();

	return worldTransform3DReticle;
}

void Player::Create2DReticle() {

}

void Player::DrawUI() { 
	sprite2DReticle_->Draw();
}