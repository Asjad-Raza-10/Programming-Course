#include <iostream>
using namespace std;

int main() {
    float b1=0, b2=0, h=0, A=0;

    cout << "Enter the length of base 1: ";
    cin >> b1;

    cout << "Enter the length of base 2: ";
    cin >> b2;

    cout << "Enter the height of the trapezoid: ";
    cin >> h;

    A = (b1 + b2) * (h / 2);

    cout << endl << "The area of the trapezoid is: " << A << endl;

    return 0;
}
