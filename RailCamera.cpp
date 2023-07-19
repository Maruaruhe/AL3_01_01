#include "RailCamera.h"

void RailCamera::Initialize(WorldTransform wt) { 
	worldTransform_.translation_ = wt.translation_;
	worldTransform_.rotation_ = wt.rotation_;

	viewProjection_.Initialize();
}
	
void RailCamera::Update() {

}