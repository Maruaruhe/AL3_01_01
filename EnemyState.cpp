#include "EnemyState.h"

void EnemyStateApproach::Update(Enemy* enemy) {
	const Vector3 velocity = {0.0f, 0.0f, -0.5f};
	enemy->move(velocity);
	if (enemy->GetTransform().translation_.z < -10.0f) {
		enemy->ChangeState(new EnemyStateLeave());
	}
}
void EnemyStateLeave::Update(Enemy* enemy) {
	const Vector3 velocity = {-0.25f, 0.25f, -0.25f};
	enemy->move(velocity);
}