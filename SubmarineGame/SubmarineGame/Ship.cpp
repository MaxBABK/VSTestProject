#include "Ship.h"
#include <iostream>

Ship::Ship()
{
	std::cout << "base constructor" << std::endl;
}

Ship::Ship(Point h, Point l)
{
	heading.x = h.x; heading.y = h.y; location.x = l.x; location.y = l.y;
}

void Ship::RotateTo(float targetRotationX, float targetRotationY)
{
	heading.x = targetRotationX; heading.y = targetRotationY;
}