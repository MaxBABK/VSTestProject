// TestApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

float cube(float num);

int main()
{
    float num1;
    float num2;
    float num3;

    std::cout << "Enter a number\n";

    std::cin >> num1;

    std::cout << "Enter a number\n";

    std::cin >> num2;

    std::cout << "Enter a number\n";

    std::cin >> num3;

    float sum = num1 + num2 + num3;

    std::cout << "sum: " << sum << "\n";

    std::cout << "average: " << sum/3 << "\n";

    std::cout << "cube1: " << cube(num1) << "\n";
    std::cout << "cube2: " << cube(num2) << "\n";
    std::cout << "cube3: " << cube(num3) << "\n";
}

float cube(float num)
{

    return num * num * num;
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
