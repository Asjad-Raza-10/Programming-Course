#include <iostream>
using namespace std;

int main()
{
    int num = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0;

    cout << "Enter a 4 digit number: ";
    cin >> num;

    if (num / 100000 != 0)
        cout << "Enter a 4 digit number only";
    else
    {

        d1 = (num % 10000) / 1000;
        d2 = (num % 1000) / 100;
        d3 = (num % 100) / 10;
        d4 = num % 10;

        if (d1 == 0)
            cout << "zero ";
        else if (d1 == 1)
            cout << "one ";
        else if (d1 == 2)
            cout << "two ";
        else if (d1 == 3)
            cout << "three ";
        else if (d1 == 4)
            cout << "four ";
        else if (d1 == 5)
            cout << "five ";
        else if (d1 == 6)
            cout << "six ";
        else if (d1 == 7)
            cout << "seven ";
        else if (d1 == 8)
            cout << "eight ";
        else
            cout << "nine ";

        if (d2 == 0)
            cout << "zero ";
        else if (d2 == 1)
            cout << "one ";
        else if (d2 == 2)
            cout << "two ";
        else if (d2 == 3)
            cout << "three ";
        else if (d2 == 4)
            cout << "four ";
        else if (d2 == 5)
            cout << "five ";
        else if (d2 == 6)
            cout << "six ";
        else if (d2 == 7)
            cout << "seven ";
        else if (d2 == 8)
            cout << "eight ";
        else
            cout << "nine ";

        if (d3 == 0)
            cout << "zero ";
        else if (d3 == 1)
            cout << "one ";
        else if (d3 == 2)
            cout << "two ";
        else if (d3 == 3)
            cout << "three ";
        else if (d3 == 4)
            cout << "four ";
        else if (d3 == 5)
            cout << "five ";
        else if (d3 == 6)
            cout << "six ";
        else if (d3 == 7)
            cout << "seven ";
        else if (d3 == 8)
            cout << "eight ";
        else
            cout << "nine ";

        if (d4 == 0)
            cout << "zero ";
        else if (d4 == 1)
            cout << "one ";
        else if (d4 == 2)
            cout << "two ";
        else if (d4 == 3)
            cout << "three ";
        else if (d4 == 4)
            cout << "four ";
        else if (d4 == 5)
            cout << "five ";
        else if (d4 == 6)
            cout << "six ";
        else if (d4 == 7)
            cout << "seven ";
        else if (d4 == 8)
            cout << "eight ";
        else
            cout << "nine ";

    }

    cout << endl;
    return 0;
}
