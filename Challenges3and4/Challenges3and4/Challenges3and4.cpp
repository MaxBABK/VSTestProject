// Challenges3and4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Car.h"
#include "Airplane.h"
#include "Boat.h"

bool IsLeapYear(int year);
void Factorize(int value);
int GetUserInput();

template<typename T>
T ArrayMaxVal(T values[], int size);


int main()
{
    std::cout << IsLeapYear(2016) << std::endl;
    std::cout << IsLeapYear(2020) << std::endl;
    std::cout << IsLeapYear(2024) << std::endl;

    std::cout << IsLeapYear(2100) << std::endl;
    std::cout << IsLeapYear(2200) << std::endl;

    std::cout << IsLeapYear(2000) << std::endl;
    std::cout << IsLeapYear(2400) << std::endl;

    Factorize(GetUserInput());

    int ints[] = {0, 1};
    float floats[] = {0.0f, -1.5F, 3, 3.1F};
    double doubles[] = {-1.5, -33, -3.1 };
    std::cout << ArrayMaxVal(ints, 2) << std::endl;
    std::cout << ArrayMaxVal(floats, 4) << std::endl;
    std::cout << ArrayMaxVal(doubles, 3) << std::endl;
    
    Car myCar;
    Boat myBoat;
    Airplane myAirplane;

    myCar.Drive(10.5F);
    myBoat.Drive(100.5F);
    myAirplane.Drive(1000.5F);

}

bool IsLeapYear(int year)
{
    bool isLeapYear = false;

    if (year % 4 == 0)
    {
        bool mod100Is0 = year % 100 == 0;

        if ( !mod100Is0 || (mod100Is0 && year % 400 == 0))
        {
            isLeapYear = true;
        }
    }

    return isLeapYear;
}

int GetUserInput()
{
    int inputValue;

    std::cout << "Enter a positive integer" << std::endl;

    do
    {
        std::cin >> inputValue;

        if (std::cin.fail() || inputValue < 0) 
        {
            std::cin.clear();
            std::cin.ignore(999, '\n');
            std::cout << "Not a valid number!" << std::endl;
        }
        else
        {
            break;
        }
    }
    while (true);
    return inputValue; 
}


void Factorize(int value)
{
    if (value <= 1)
        return;

    float root = sqrt(value);

    // Check from 2 to square root of n

    for (int i = 2; i <= root; i++)
    {
        while (value % i == 0)
        {
            std::cout << i << std::endl;
            value /= i;

        }
        root = sqrt(value);
    }
    if (value != 1)
    {
        std::cout << value << std::endl;
    }
}

// Assumes array is greater than size 0
template<typename T>
T ArrayMaxVal(T values[], int size)
{
    T maxVal = values[0];
    for (int i = 1; i < size; i++)
    {
        if (values[i] > maxVal)
        {
            maxVal = values[i];
        }
    }

    return maxVal;
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
