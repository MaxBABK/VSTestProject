// Week4Challenges.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

#include "AStar.h"


template<typename T>
void SortVector(std::vector<T>& v);
void PrintVector(std::vector <int> const& a);


void FillVector(std::vector<int>& v, int amount, int max);
void FillVector(std::vector<float>& v, int amount, int max);

int main()
{
    //std::cout << "Hello World!\n";
    //std::vector<int> v;
    //FillVector(v, 10, 500);
    //PrintVector(v);
    //SortVector(v);
    //PrintVector(v);

    map m;
    point s, e(7, 7);
    AStar as;

    if (as.search(s, e, m)) {
        std::list<point> path;
        int c = as.path(path);
        for (int y = -1; y < 9; y++) {
            for (int x = -1; x < 9; x++) {
                if (x < 0 || y < 0 || x > 7 || y > 7 || m(x, y) == 1)
                    std::cout << char(0xdb);
                else {
                    if (std::find(path.begin(), path.end(), point(x, y)) != path.end())
                        std::cout << "x";
                    else std::cout << ".";
                }
            }
            std::cout << "\n";
        }

        std::cout << "\nPath cost " << c << ": ";
        for (std::list<point>::iterator i = path.begin(); i != path.end(); i++) {
            std::cout << "(" << (*i).x << ", " << (*i).y << ") ";
        }
    }
    std::cout << "\n\n";
    return 0;



}


template<typename T>
void SortVector(std::vector<T>& v)
{
    std::sort(v.begin(), v.end());
}


void PrintVector(std::vector <int> const& a) {
    std::cout << "The vector elements are : ";

    for (unsigned int i = 0; i < a.size(); i++)
        std::cout << a.at(i) << ' ';
}

void FillVector(std::vector<int>& v, int amount, int max)
{
    for (int i = 0; i < amount; i++)
    {
        v.push_back(std::rand()%max);

    }

}

void FillVector(std::vector<float>& v, int amount, int max)
{
    for (int i = 0; i < amount; i++)
    {


    }

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
