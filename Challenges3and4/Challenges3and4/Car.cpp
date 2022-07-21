#include "Car.h"
#include <iostream>

void Car::Drive(float mileage)
{
	Vehicle::Drive(mileage);
	std::cout << "honk" << std::endl;
}

