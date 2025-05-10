
#include <iostream>
using namespace std;

int main()
{
    int X = 0, Y = 0;

    cout << "Enter the value of X: ";
    cin >> X;

    cout << "Enter the value of Y: ";
    cin >> Y;

    if (Y == 0)
    {
        cout << "False, cannot divide by 0" << endl;
    }
    else if (X % Y == 0)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }

    cout << endl;
    return 0;
}
