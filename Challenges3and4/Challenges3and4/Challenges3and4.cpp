// Challenges3and4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

bool IsLeapYear(int year);
void Factorize(int value);
int GetUserInput();

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
            std::cin.ignore(99, '\n');
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



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
