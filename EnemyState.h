#pragma once
#include "Enemy.h"

class Enemy;

class BaseEnemyState {
public:
	virtual void Update(Enemy* enemy) = 0;
};

class EnemyStateApproach : public BaseEnemyState {
public:
	void Update(Enemy* enemy);
};

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* enemy);
};