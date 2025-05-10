#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x = 0;
    cout << "Enter value to calculate its log: ";
    cin >> x;

    if (x < 1)
    {
        cout << "Invalid Input.";
        return 0;
    }

    float log = ((x - 1) / float(x));

    for (int i = 2; i <= 7; i++)
    {
        log += (0.5) * pow(((x - 1) / float(x)), i);
    }

    cout << "The approximate value of log " << x << " is: " << log;
     
}