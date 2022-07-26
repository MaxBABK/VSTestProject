#pragma once

#include "Ship.h"

class Enemy : public Ship
{
private:

	int priority;

public:

	Enemy();
	Enemy(int p, float x, float y);
	~Enemy() {};

	int GetPriority() { return priority; }
	void Die() {}
};

