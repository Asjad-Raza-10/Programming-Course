#include <iostream>
using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 0, b = 0;

    cout << "Enter a number A: ";
    cin >> a;

    cout << "Enter another number B: ";
    cin >> b;

    swap(&a, &b);

    cout << endl << "A is: " << a << endl << "B is: " << b << endl;

    return 0;
}