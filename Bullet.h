#pragma once
#include "Model.h"
#include "Vector3.h"
#include <WorldTransform.h>

class Bullet {
public:
	//Bullet();
	//~Bullet();

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
};