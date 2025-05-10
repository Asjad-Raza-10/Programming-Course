#include <iostream>
using namespace std;

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 0, b = 0, c = 0;

    cout << "Enter the 1st number: ";
    cin >> a;

    cout << "Enter the 2nd number: ";
    cin >> b;

    cout << "Enter the 3rd number: ";
    cin >> c;

    cout << endl << "Sum of all three numbers is: " << sum(c, sum(a, b));

    return 0;
}
