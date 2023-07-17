#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <assert.h>
#include <Input.h>
#include "Matrix.h"
#include "Vec3.h"
#include <list>

class Skydome {
public:
	void Initialize(Model* model/*, const Vector3& position*/);

	void Update();

	void Draw(ViewProjection viewProjection_);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
