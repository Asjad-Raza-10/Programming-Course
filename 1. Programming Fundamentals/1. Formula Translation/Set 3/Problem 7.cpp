#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float l = 0, w = 0, h = 0, b = 0, H = 0, r = 0;
    float V = 0;

    // Volume of Box
    cout << "Enter length, width, and height of the box: ";
    cin >> l >> w >> h;
    V = l * w * h;
    cout << "The volume of the box is: " << V << endl;
    V = 0; // Resetting volume for reuse

    // Volume of Prism
    cout << "Enter the base length and height of the triangle for the prism: ";
    cin >> b >> h; // Reusing h for the height of the triangle
    cout << "Enter the height of the prism: ";
    cin >> H;
    V = 0.5 * b * h * H;
    cout << "The volume of the triangular prism is: " << V << endl;
    V = 0; // Resetting volume for reuse

    // Volume of Cylinder
    cout << "Enter the radius of the base and height of the cylinder: ";
    cin >> r >> H; // Reusing H for height of the cylinder
    V = 3.14 * pow(r, 2) * H;
    cout << "The volume of the cylinder is: " << V << endl;
    V = 0; // Reset volume for reuse

    // Volume of Sphere
    cout << "Enter the radius of the sphere: ";
    cin >> r; // Reusing r for the radius of the sphere
    V = (4.0 / 3.0) * 3.14 * pow(r, 3);
    cout << "The volume of the sphere is: " << V << endl;
    

    return 0;
}
