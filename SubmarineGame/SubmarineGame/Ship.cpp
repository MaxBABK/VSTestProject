#include "Ship.h"
#include <iostream>

Ship::Ship()
{
	std::cout << "base constructor" << std::endl;
	heading = new Point(0,1);
	location = new Point(0, 1);
}

Ship::~Ship()
{
	std::cout << "Destroying memory for ship" << std::endl;
	delete heading;
	delete location;
	heading = nullptr;
	location = nullptr;
}

Ship::Ship(Point* h, Point* l)
{
	heading = h;
	location = l;
}

void Ship::RotateTo(float targetRotationX, float targetRotationY)
{
	heading->x = targetRotationX; heading->y = targetRotationY;
}