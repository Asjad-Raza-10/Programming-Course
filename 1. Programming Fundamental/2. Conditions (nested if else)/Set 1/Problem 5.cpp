#include <iostream>
using namespace std;

int main()
{
    int num = 0;

    cout << "Enter an integer: ";
    cin >> num;

    if (num > 0)
    {
        if (num % 2 == 0)
        {
            cout << "The number is positive even." << endl;
        }
        else
        {
            cout << "The number is positive odd." << endl;
        }
    }
    else if (num < 0)
    {
        if (num % 2 == 0)
        {
            cout << "The number is negative even." << endl;
        }
        else
        {
            cout << "The number is negative odd." << endl;
        }
    }
    else
    {
        cout << "The number is zero." << endl;
    }

    cout << endl;
    return 0;
}
