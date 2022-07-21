#pragma once
#include "Vehicle.h"
class Boat :
    public Vehicle
{

public:
    void Drive(float mileage) override;
};

