#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0, c = 0, r = 0;

    cout << "Enter the first side a of triangle: ";
    cin >> a;

    cout << endl << "Enter the second side b of triangle: ";
    cin >> b;

    cout << endl << "Enter the second third c of triangle: ";
    cin >> c;

    r = sqrt((a * a) + (b * b));

    if (r == c)
        cout << endl << "It is a right-angled triangle";
    else
        cout << endl << "Not a right-angled triangle";
    
    cout << endl;
    return 0;
}
