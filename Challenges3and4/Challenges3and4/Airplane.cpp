#include "Airplane.h"
#include <iostream>

void Airplane::Drive(float mileage)
{
	Vehicle::Drive(mileage);
	std::cout << "whoosh" << std::endl;
}