#include "Enemy.h"
#include <assert.h>
#include "Matrix.h"

Enemy::Enemy() { 
	state = new EnemyStateApproach(); 
}
Enemy::~Enemy() { 
	//delete state;
}
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	textureHandle_ = TextureManager::Load("Angel.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}
void Enemy::Update() {
	state->Update(this);
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
	/*velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);*/
}
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
void Enemy::move(const Vector3& velocity) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}
//void Enemy::Approach() { 
//	move({0.0f, 0.0f, -0.5f});
//	if (worldTransform_.translation_.z < -10.0f) {
//		ChangeState(new EnemyStateLeave());
//	}
//}
//void Enemy::Leave() { 
//	move({-0.25f, 0.25f, 0.0f});
//}
void Enemy::ChangeState(BaseEnemyState* newState) { 
	delete state;
	state=newState;
}

//void BaseEnemyState::Update(Enemy* enemy) {
//
//}
void EnemyStateApproach::Update(Enemy* enemy) {
	const Vector3 velocity = {0.0f, 0.0f, -0.5f};
	enemy->move(velocity);
	if (enemy->GetTransform().translation_.z < -10.0f) {
		enemy->ChangeState(new EnemyStateLeave());
	}
}
void EnemyStateLeave::Update(Enemy* enemy) {
	const Vector3 velocity = {-0.25f, 0.25f, -0.25f};
	enemy->move(velocity);
}
//void (Enemy::*Enemy::spFuncTable[])() = {
//	&Enemy::Approach,
//	&Enemy::Leave
//};