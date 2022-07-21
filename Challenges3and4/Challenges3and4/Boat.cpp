#include "Boat.h"
#include <iostream>

void Boat::Drive(float mileage)
{
	Vehicle::Drive(mileage);
	std::cout << "swish" << std::endl;
}