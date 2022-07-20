// Challenges3and4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

bool IsLeapYear(int year);

int main()
{
    std::cout << IsLeapYear(2016) << std::endl;
    std::cout << IsLeapYear(2020) << std::endl;
    std::cout << IsLeapYear(2024) << std::endl;

    std::cout << IsLeapYear(2100) << std::endl;
    std::cout << IsLeapYear(2200) << std::endl;

    std::cout << IsLeapYear(2000) << std::endl;
    std::cout << IsLeapYear(2400) << std::endl;
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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
