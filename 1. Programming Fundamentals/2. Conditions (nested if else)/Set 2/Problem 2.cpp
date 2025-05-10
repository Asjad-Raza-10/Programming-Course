#include <iostream>
using namespace std;

int main()
{
    int n = 0;

    cout << "Enter the year: ";
    cin >> n;
    cout << endl;

    if (n % 4 == 0)
        if (n % 100 == 0)
            if (n % 400 == 0)
                cout << "Leap Year";
            else
                cout << "Not a Leap Year";
        else
            cout << "Leap Year";
    else
        cout << "Not a Leap Year";


    cout << endl;
    return 0;
}

