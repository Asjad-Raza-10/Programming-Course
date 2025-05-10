#include <iostream>
using namespace std;

int main()
{
    int num = 0, d1 = 0, d2 = 0, d3 = 0, r = 0;

    cout << "Enter a 3 digit number: ";
    cin >> num;
    cout << endl;

    d1 = (num % 1000) / 100;
    d2 = (num % 100) / 10;
    d3 = num % 10;

    r = ((d1 * d1 * d1) + (d2 * d2 * d2) + (d3 * d3 * d3));

    if (r == num)
        cout << "It is an Armstrong number";
    else
        cout << "Not an Armstrong number";
    cout << endl;
    return 0;
}
