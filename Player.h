#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <assert.h>
#include <Input.h>
#include "Matrix.h"

class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	Input* input_ = nullptr;

	uint32_t textureHandle_ = 0u;

	float inputFloat3[3] = {0, 0, 0};
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 17;
};