#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Skydome {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection_);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
