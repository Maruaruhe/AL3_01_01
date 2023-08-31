#pragma once
#include <Model.h>
#include <WorldTransform.h>
#include "EnemyBullet.h"
#include "TimedCall.h"
#include <list>

class GameScene;

class Player;

class Enemy;

class BaseEnemyState {
public:
	virtual void Update(Enemy* enemy) = 0;
};

class EnemyStateApproach : public BaseEnemyState {
public:
	void Update(Enemy* enemy);
};

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* enemy);
};

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void ChangeState(BaseEnemyState* newState);
	void move(const Vector3& velocity);

	//void Fire();
	Vector3 SetPosition(const Vector3& position) { return position; }
	Vector3 SetVelocity(const Vector3& velocity) { return velocity; }
	WorldTransform GetTransform() { return worldTransform_; }

	//void ResetTime();

	Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }

	//static const int kFireInterval = 120;

	void OnCollision();

	//const std::list<EnemyBullet*>& GetBullets() const { return enemyBullets_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() { return isDead_; }

private:
	GameScene* gameScene_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	BaseEnemyState* state;

	Player* player_ = nullptr;

	bool isDead_;
};