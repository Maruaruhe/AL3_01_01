#pragma once
#include "Player.h"
#include "Enemy.h"

class CollisionManager {
public:

	void Initialize();
	void Update();

	void Colliders();

	void CheckAllCollision();

	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

private:
	std::list<Collider*> colliders_;

	Player* player_;
	Enemy* enemy_;

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
