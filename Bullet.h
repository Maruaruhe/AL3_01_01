#pragma once
#include "Model.h"
#include "Vector3.h"

class Bullet {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model;
};
