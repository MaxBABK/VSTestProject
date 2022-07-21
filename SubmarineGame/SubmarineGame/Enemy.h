#pragma once
class Enemy
{
private:
	float locationX;
	float locationY;

	int priority;

public:
	float GetLocationX() { return locationX; }
	float GetLocationY() { return locationY; }
	int GetPriority() { return priority; }
};

