#pragma once
#include <WorldTransform.h>
#include "ViewProjection.h"

#include "Matrix.h"
#include "ImGuiManager.h"

class RailCamera {
public:
	void Initialize(WorldTransform wt);

	void Update();

	ViewProjection GetViewProjection() { return viewProjection_; }

	private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
