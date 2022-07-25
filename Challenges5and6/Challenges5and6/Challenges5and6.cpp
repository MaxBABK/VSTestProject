// Challenges5and6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<class T>
void GetValueFromUser()
{
    T x;

    std::cout << "Enter a value " << std::endl;
    std::cin >> x;

    T* xptr = new T(x);

    std::cout << "Value x: " << *xptr << " stored at " << xptr << std::endl;

    delete xptr;
}


int main()
{

    //Write a program that asks the user to enter integers to be stored in the variables 'a' and 'b'.
    //Then create two integer pointers named ptrA and ptrB.Assign the values of 'a' and 'b' to ptrA and ptrB, and display them.
    //Take an input variable and display the same value by pointer.
    int a;
    int b;

    std::cout << "Enter integer A\n";

    std::cin >> a;


    std::cout << "Enter integer B\n";
    std::cin >> b;
    

    int* ptrA = new int(a);
    int* ptrB = new int(b);

    std::cout << "Value a: " << *ptrA << " stored at " << ptrA << std::endl;
    std::cout << "Value b: " << *ptrB << " stored at " << ptrB << std::endl;
    
    delete ptrA;
    delete ptrB;


    GetValueFromUser();
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
