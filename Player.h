#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <assert.h>
#include <Input.h>
#include "Matrix.h"
#include "Bullet.h"

class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	Input* input_ = nullptr;

	Bullet* bullet_ = nullptr;

	uint32_t textureHandle_ = 0u;

	float inputFloat3[3] = {0, 0, 0};

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 17;

	const float kRotSpeed = 0.02f;
};