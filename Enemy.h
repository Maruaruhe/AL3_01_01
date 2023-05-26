#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Enemy {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	enum class Phase {
		Approach,
		Leave,
	};

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	Phase phase_;
};
