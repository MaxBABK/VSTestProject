#include "Vehicle.h"

Vehicle::Vehicle()
{
	mileage = 0;
}

void Vehicle::Drive(float mileage)
{
	mileage += mileage;
}