#include <iostream>
using namespace std;

int sum(int a, int b)
{
    return a + b;
}

int difference(int a, int b)
{
    return a - b;
}

int product(int a, int b)
{
    return a * b;
}

float division(float a, float b)
{
    return a / b;
}


int main()
{
    int a = 0, b = 0;
    char operation = NULL;

    cout << "Enter 1st number: ";
    cin >> a;

    cout << "Enter 2nd number: ";
    cin >> b;

    cout << "Enter the desired operation (+, -, *, /): ";
    cin >> operation;

    cout << endl << "Ouput is: ";

    if (operation == '+')
    {
        cout << sum(a, b);
    }
    else if (operation == '-')
    {
        cout << difference(a, b);
    }
    else if (operation == '*')
    {
        cout << product(a, b);
    }
    else if (operation == '/')
    {
        cout << division(float(a), float(b));
    }

    return 0;
}
