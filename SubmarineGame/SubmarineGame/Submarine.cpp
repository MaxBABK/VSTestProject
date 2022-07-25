#include "Submarine.h"
#include <iostream>

Submarine::Submarine() : Ship(Point(0, 1), Point(0, 0))
{

}

Submarine::~Submarine()
{

}


void Submarine::Shoot()
{
	std::cout << "bang" << std::endl;
}