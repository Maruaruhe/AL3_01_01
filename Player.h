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

	const std::list<Bullet*>& GetBullets() const { return bullets_; }

	void SetParent(const WorldTransform* parent);

	WorldTransform GiveWorld() { return worldTransform_; }

	void DrawUI();

private:
	WorldTransform worldTransform_;

	WorldTransform worldTransform3DReticle_;

	Sprite* sprite2DReticle_ = nullptr;

	Model* model_ = nullptr;
	Model* reticleModel_ = nullptr;
	Input* input_ = nullptr;

	std::list<Bullet*> bullets_;

	uint32_t textureHandle_ = 0u;

	float inputFloat3[3] = {0, 0, 0};

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 17;

	const float kRotSpeed = 0.02f;
};