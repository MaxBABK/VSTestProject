#pragma once

#include "Ship.h"

class Enemy : public Ship
{
private:

	int priority;

public:

	int GetPriority() { return priority; }
	void Die() {}
};

