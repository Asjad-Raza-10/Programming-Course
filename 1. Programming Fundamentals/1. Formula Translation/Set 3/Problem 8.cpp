#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    float x, result;
    int choice;

    cout << "Choose the unit of the angle to input:" << endl;
    cout << "1. Radians" << endl;
    cout << "2. Degrees" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the value of x (in radians): ";
        cin >> x;

        result = x - (pow(x, 3) / 6) + (pow(x, 5) / 120) - (pow(x, 7) / 5040) + (pow(x, 9) / 362880) - (pow(x, 11) / 39916800);

        cout << "The value of sin(" << x << setprecision(3) << ") is: " << setprecision(3) << result << endl;
    } 
    else if (choice == 2) {
        cout << "Enter the value of x (in degrees): ";
        cin >> x;
        x = x * (3.14 / 180);  // Converting degrees to radians

        result = x - (pow(x, 3) / 6) + (pow(x, 5) / 120) - (pow(x, 7) / 5040) + (pow(x, 9) / 362880) - (pow(x, 11) / 39916800);

        cout << "The value of sin(" << setprecision(3) << x << " radians)  is: " << setprecision(3) << result << endl;
    } 
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
