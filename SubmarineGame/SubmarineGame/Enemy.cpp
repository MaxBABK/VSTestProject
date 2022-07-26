#include "Enemy.h"

#include <iostream>


Enemy::Enemy() : Ship(new Point(0, 1), new Point(0, 0))
{
	priority = 500;
	std::cout << "default enemy constructor" << std::endl;
}



Enemy::Enemy(int p, float x, float y) : Ship(new Point(0, 1), new Point(x, y))
{
	//std::cout << "enemy constructor" << std::endl;
	priority = p;
}
