#include <iostream>
using namespace std;

int fact(int a)
{
    int fact = 1, i = 0;

    if (a > 0)
    {
        i = a;
    }
    else
    {
        i = -1 * a;
    }

    for (i; i > 0; i--)
    {
        fact *= i;
    }

    if (a > 0)
    {
        return fact;
    }
    else
    {
        return (-1 * fact);
    }
}

int main()
{
    int a = 0;

    cout << "Enter a number: ";
    cin >> a;

    cout << endl << "Factorial of " << a << " is: " << fact(a);

    return 0;
}
