#include <iostream>
#include <cmath>
using namespace std;

int main() {

    float x1 = 0, y1 = 0;
    float x2 = 0, y2 = 0;
    float x3 = 0, y3 = 0;
    float d1 = 0, d2 = 0, d3 = 0;
    float p = 0, A = 0;

    cout << "Enter coordinates of point A (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter coordinates of point B (x2 y2): ";
    cin >> x2 >> y2;

    cout << "Enter coordinates of point C (x3 y3): ";
    cin >> x3 >> y3;

    d1 = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
    d2 = sqrt(((x2 - x3) * (x2 - x3)) + ((y2 - y3) * (y2 - y3)));
    d3 = sqrt(((x1 - x3) * (x1 - x3)) + ((y1 - y3) * (y1 - y3)));

    cout << "Distance between A and B (d1): " << d1 << endl;
    cout << "Distance between B and C (d2): " << d2 << endl;
    cout << "Distance between A and C (d3): " << d3 << endl;

    // Calculating area using Hero's Formula
    p=(d1+d2+d3)/2;
    A=sqrt(p*(p-d1)*(p-d2)*(p-d3));

    cout << "Area of the triangle formed by points A, B, and C is: " << A << endl;

    return 0;
}
