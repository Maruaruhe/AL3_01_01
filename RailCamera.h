#pragma once
#include <WorldTransform.h>
#include "ViewProjection.h"
#include <Input.h>
#include "Matrix.h"
#include "ImGuiManager.h"

class RailCamera {
public:
	//void Initialize(WorldTransform wt);
	void Initialize(Vector3 translation,Vector3 rotation);

	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
