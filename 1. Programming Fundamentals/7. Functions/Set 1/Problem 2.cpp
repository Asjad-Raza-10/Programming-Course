#include <iostream>
using namespace std;

int swap(int *x, int *y)
{
    int *temp = x;
    x = y;
    y = temp;

    return 0;
}

int main()
{
    int a = 0, b = 0;
    cout << "Enter value of a: ";
    cin >> a;

    cout << "Enter value of b: ";
    cin >> b;

    swap(a, b);

    cout << "Value of a is: " << a << endl;
    cout << "Value of b is: " << b;


    return 0;
}