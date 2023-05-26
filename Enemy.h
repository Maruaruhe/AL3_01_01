#pragma once
#include <Model.h>
#include <WorldTransform.h>

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

	/*void Approach();
	void Leave();*/
	void ChangeState(BaseEnemyState* newState);
	void move(const Vector3& velocity);

	/*enum class Phase {
	    Approach,
	    Leave,
	};*/
	Vector3 SetPosition(const Vector3& position) { return position; }
	Vector3 SetVelocity(const Vector3& velocity) { return velocity; }
	WorldTransform GetTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	BaseEnemyState* state;
};