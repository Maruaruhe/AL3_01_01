#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <assert.h>
#include <Input.h>
#include "Matrix.h"
#include "Vec3.h"
#include "Bullet.h"
#include <Sprite.h>
#include <list>
#include "AABB.h"

class Player {
public:
	Player();
	~Player();

	void Initialize(Model* model, Model* reticleModel, uint32_t textureHandle, Vector3 playerPosition);

	void Update(ViewProjection viewProjection);

	void Draw(ViewProjection viewProjection_);

	void Attack();

	Vector3 GetWorldPosition();

	void OnCollision();

	bool SetOnCollision(bool a) { return isCollision = a; }

	const std::list<Bullet*>& GetBullets() const { return bullets_; }

	void SetParent(const WorldTransform* parent);
	void SetDirection(Direction direction) { direction_ = direction; }

	WorldTransform GiveWorld() { return worldTransform_; }
	WorldTransform GivePreWorld() { return worldTransform_; }
	void SetPosition(Vector3 worldtransform) { worldTransform_.translation_ = worldtransform; }

	void DrawUI();

private:
	WorldTransform worldTransform_;
	WorldTransform preWorldTransform_;
	Direction direction_;

	WorldTransform worldTransform3DReticle_;

	Sprite* sprite2DReticle_ = nullptr;

	Model* model_ = nullptr;
	Model* reticleModel_ = nullptr;
	Input* input_ = nullptr;

	std::list<Bullet*> bullets_;

	uint32_t textureHandle_ = 0u;

	float inputFloat3[3] = {0, 0, 0};

	bool isCollision = false;

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 17;

	const float kRotSpeed = 0.02f;
};