#pragma once
#include "Point.h"

class Ship
{

private:


public:

	Point heading;
	Point location;

	Ship();

	Ship(Point h, Point l);

	void RotateTo(float targetRotationX, float targetRotationY);
	
};

