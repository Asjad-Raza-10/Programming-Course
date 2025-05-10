#include <iostream>
#include <cmath>
using namespace std;

int main() 
{

    float x1 = 0, y1 = 0, x2 = 0, y2 = 0, d = 0;

    cout << "Enter coordinates of point A (x1, y1): ";
    cin >> x1 >> y1;

    cout << "Enter coordinates of point B (x2, y2): ";
    cin >> x2 >> y2;

    //using variable d for distance
    d = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));

    cout << "Distance between A and B: " << d << endl;

    return 0;
}
