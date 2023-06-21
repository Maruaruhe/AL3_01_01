#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <assert.h>
#include <Input.h>
#include "Matrix.h"
#include "Vec3.h"
#include "Bullet.h"
#include <list>

class Player {
public:
	Player();
	~Player();

	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	Input* input_ = nullptr;

	std::list<Bullet*> bullets_;

	uint32_t textureHandle_ = 0u;

	float inputFloat3[3] = {0, 0, 0};

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 17;

	const float kRotSpeed = 0.02f;
};