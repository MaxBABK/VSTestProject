// SubmarineGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Enemy.h"
#include "Submarine.h"

#include <vector>
#include <math.h> 

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void LaunchAttack(std::vector<Enemy*> &enemies);
int GetHighestPriorityTarget(std::vector<Enemy*> enemies, Submarine* sub);

float GetRotationalDistance(float x1, float y1, float x2, float y2);

int main()
{
    std::cout << "Hello World!\n";

    std::vector<Enemy*> enemies;

    Submarine* sub = new Submarine();

    LaunchAttack(enemies);
    while (enemies.size() > 0)
    {
        int closestEnemy = GetHighestPriorityTarget(enemies, sub);
        if (closestEnemy < 0)
        {
            break;
        }
        Enemy* enemyToKill = enemies.at(closestEnemy);
        sub->RotateTo(enemyToKill->location->x, enemyToKill->location->y);
        sub->Shoot();
        enemyToKill->Die();
        enemies.erase(enemies.begin() + closestEnemy);
        delete enemyToKill;
        enemyToKill = nullptr;
    }
   
    enemies.clear();

    delete sub;
    sub = nullptr;


    //Enemy* en1 = new Enemy();
    //delete en1;
    //en1 = nullptr;

    //Enemy* en2 = new Enemy(1, 2.0F, 3.0F);
    //delete en2;
    //en2 = nullptr;


    _CrtDumpMemoryLeaks();
}

void LaunchAttack(std::vector<Enemy*>& enemies)
{
    // place enemies
    
    enemies.push_back(new Enemy(50, 2.0f, -1.0f));
    enemies.push_back(new Enemy(4, -3.0f, 1.0f));
    enemies.push_back(new Enemy(4, 2.0f, 6.0f));
    enemies.push_back(new Enemy(4, -5.0f, -4.0f));
    //enemies.push_back(new Enemy(4, -5.0f, -4.0f));
    //enemies.push_back(new Enemy(4, -5.0f, -4.0f));
    //enemies.push_back(new Enemy(4, -5.0f, -4.0f));
}

int GetHighestPriorityTarget(std::vector<Enemy*> enemies, Submarine* sub)
{
    // Get submarine direction
    // iterate over enemies, get rotational distances, but look at priority as well
    int highestPrio = 500;
    float shortestDistance = -1;

    int prioEnemy = -1;

    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy* currEnemy = enemies.at(i);

        if (currEnemy->GetPriority() <= highestPrio)
        {
            float rotationalDistance = GetRotationalDistance(sub->heading->x, sub->heading->y, currEnemy->location->x, currEnemy->location->y);
            if (currEnemy->GetPriority() < highestPrio || (shortestDistance < 0 || rotationalDistance < shortestDistance) )
            {
                // Math issue here so need to see current values
                shortestDistance = rotationalDistance;
                highestPrio = currEnemy->GetPriority();
                prioEnemy = i;
            }
        }
    }

    return prioEnemy;
}

float GetRotationalDistance(float x1, float y1, float x2, float y2)
{
    // not right
    float angle = acos((x1 * x2 + y1 * y2) / (sqrt(x1*x1 + y1*y1) * sqrt(x2*x2 + y2*y2)));

    return angle;
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
