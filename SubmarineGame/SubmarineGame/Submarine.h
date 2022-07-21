#pragma once
class Submarine
{
private:
	//Quaternion
	float directionX;
	float directionY;

public:
	void RotateTo(float targetLocationX, float targetLocationY) { directionX = targetLocationX; directionY = targetLocationY; }
	void Shoot() {};

	float GetRotationX() { return directionX;  }
	float GetRotationY() { return directionY; }
};

