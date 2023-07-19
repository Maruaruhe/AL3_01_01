﻿#include "Skydome.h"

void Skydome::Initialize(Model* model) {

	model_ = model;

	worldTransform_.Initialize();
}
void Skydome::Update() {

}
void Skydome::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_);
}