// Week4Challenges.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
void SortVector(std::vector<T>& v);
void PrintVector(std::vector <int> const& a);


void FillVector(std::vector<int>& v, int amount, int max);
void FillVector(std::vector<float>& v, int amount, int max);

int main()
{
    std::cout << "Hello World!\n";
    std::vector<int> v;
    FillVector(v, 10, 500);
    PrintVector(v);
    SortVector(v);
    PrintVector(v);
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
