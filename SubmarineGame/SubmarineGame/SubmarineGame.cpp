// SubmarineGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Enemy.h"
#include "Submarine.h"

#include <vector>

void LaunchAttack();
int GetHighestPriorityTarget(std::vector<Enemy> enemies, Submarine& sub);

float GetRotationalDistance(float x1, float y1, float x2, float y2);

int main()
{
    std::cout << "Hello World!\n";

    std::vector<Enemy> enemies;

    Submarine sub;

    LaunchAttack();
    while (enemies.size() > 0)
    {
        int closestEnemy = GetHighestPriorityTarget(enemies, sub);
        if (closestEnemy < 0)
        {
            break;
        }
        sub.RotateTo(enemies.at(closestEnemy).GetLocationX(), enemies.at(closestEnemy).GetLocationY());
        sub.Shoot();
    }
   
    // rotate sub
    // shoot at target, remove from list
}

void LaunchAttack()
{
    // place enemies

}

int GetHighestPriorityTarget(std::vector<Enemy> enemies, Submarine& sub)
{
    // Get submarine direction
    // iterate over enemies, get rotational distances, but look at priority as well
    int highestPrio = 500;
    float shortestDistance = -1;

    int prioEnemy = -1;

    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy& currEnemy = enemies.at(i);
        if (currEnemy.GetPriority() <= highestPrio)
        {
            float rotationalDistance = GetRotationalDistance(sub.GetRotationX(), sub.GetRotationY(), currEnemy.GetLocationX(), currEnemy.GetLocationY());
            if ( shortestDistance < 0 || rotationalDistance < shortestDistance )
            {
                shortestDistance = rotationalDistance;
                highestPrio = currEnemy.GetPriority();
                prioEnemy = i;
            }
        }
    }

    return prioEnemy;
}

float GetRotationalDistance(float x1, float y1, float x2, float y2)
{
    // Do math stuff with cosine
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
