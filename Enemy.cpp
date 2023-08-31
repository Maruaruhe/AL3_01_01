#include "Enemy.h"
#include <assert.h>
#include "Matrix.h"
#include "Vec3.h"
#include "Player.h"
#include <assert.h>

Enemy::Enemy() { 
	state = new EnemyStateApproach(); 
}
Enemy::~Enemy() { 
}
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	model_ = Model::Create();
	assert(model);
	textureHandle_ = TextureManager::Load("Angel.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	//ResetTime();
}
void Enemy::Update() {
	state->Update(this);
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
void Enemy::move(const Vector3& velocity) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::ChangeState(BaseEnemyState* newState) { 
	state=newState;
}

void EnemyStateApproach::Update(Enemy* enemy) {
	const Vector3 velocity = {0.0f, 0.0f, 0.0f};
	enemy->move(velocity);
	if (enemy->GetTransform().translation_.z < -10.0f) {
		enemy->ChangeState(new EnemyStateLeave());
	}
}
void EnemyStateLeave::Update(Enemy* enemy) {
	const Vector3 velocity = {-0.25f, 0.25f, -0.25f};
	enemy->move(velocity);
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPosition;

	worldPosition.x = worldTransform_.matWorld_.m[3][0];
	worldPosition.y = worldTransform_.matWorld_.m[3][1];
	worldPosition.z = worldTransform_.matWorld_.m[3][2];

	return worldPosition;
}

void Enemy::OnCollision() {

}