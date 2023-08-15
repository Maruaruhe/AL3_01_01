#include "Enemy.h"
#include <assert.h>
#include "Matrix.h"
#include "Vec3.h"
#include "Player.h"
#include <assert.h>
#include "CollisionConfig.h"

Enemy::Enemy() { 
	state = new EnemyStateApproach(); 
}
Enemy::~Enemy() { 
	 for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	model_ = Model::Create();
	assert(model);
	textureHandle_ = TextureManager::Load("Angel.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	ResetTime();

	SetCollisionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(~kCollisionAttributeEnemy);
}
void Enemy::Update() {
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
	});

	state->Update(this);
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

}
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}
void Enemy::move(const Vector3& velocity) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::Fire() {
	assert(player_);
	const float kBulletSpeed = 1.0f;


	/*Vector3 velocity(0, 0, kBulletSpeed);
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);*/
	
	Vector3 distance = Subtract(GetWorldPosition(),player_->GetWorldPosition());
	Vector3 normalize = Normalize(distance);
	Vector3 velocity = {};
	velocity.x = -normalize.x;
	velocity.y = -normalize.y;
	velocity.z = -normalize.z;

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);
}

void Enemy::ResetTime() { 

	Fire();

	std::function<void(void)> callback = std::bind(&Enemy::ResetTime, this);
	TimedCall* timedCall = new TimedCall(callback, 30);
	timedCalls_.push_back(timedCall);

}

void Enemy::ChangeState(BaseEnemyState* newState) { 
	delete state;
	state=newState;
}

void EnemyStateApproach::Update(Enemy* enemy) {
	const Vector3 velocity = {0.0f, 0.0f, -0.05f};
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