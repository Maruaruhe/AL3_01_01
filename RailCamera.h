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

	void SetPosition(Vector3 translation) { worldTransform_.translation_ = translation; }

	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_;
};
