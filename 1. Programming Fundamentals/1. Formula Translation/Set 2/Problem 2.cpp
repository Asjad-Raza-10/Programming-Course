#include <iostream>
#include<cmath>

using namespace std;
int main()
{
    
    int a = 0, b = 0, c = 0;
    float o = 0.0;

    cout << "Enter the length of side a" << endl;
    cin >> a;

    cout << "Enter the length of side b" << endl;
    cin >> b;

    cout << "Enter the length of side c" << endl;
    cin >> c;

    o = acos((pow(a, 2) - pow(b, 2) + pow(c, 2)) / (2 * a * c));

    cout << "The angle = " << o << endl;


    system("pause");

    return 0;
}
