#include "Skydome.h"
#include <assert.h>

void Skydome::Initialize(Model* model, const Vector3& position) {

	model_ = Model::Create();
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}
void Skydome::Update() {

}
void Skydome::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_);
}