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