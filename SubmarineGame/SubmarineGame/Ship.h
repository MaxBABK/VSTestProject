#pragma once
#include "Point.h"

class Ship
{

private:


public:

	Point heading;
	Point location;

	Ship () { }
	Ship(Point h, Point l) { heading.x = h.x; heading.y = h.y; location.x = l.x; location.y = l.y; }

	void RotateTo(float targetRotationX, float targetRotationY) { heading.x = targetRotationX; heading.y = targetRotationY; }
	
};

