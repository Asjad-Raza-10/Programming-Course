#include <iostream>
using namespace std;

int main()
{
    int age = 0, n = 0, surcharge = 500;

    cout << "The base insurance charge is 500 Rs" << endl;
    
    cout << "Enter driver's age: ";
    cin >> age;

    cout << "Enter the number of accidents: ";
    cin >> n;

    if (age < 25)
    {
        surcharge += 100;
    }

    if (n == 1)
    {
        surcharge += 50;
    }
    else if (n == 2)
    {
        surcharge += 125;
    }
    else if (n == 3)
    {
        surcharge += 225;
    }
    else if (n == 4)
    {
        surcharge += 375;
    }
    else if (n == 5)
    {
        surcharge += 575;
    }
    else if (n >= 6)
    {
        cout << "No insurance for 6 or more accidents." << endl;
        return 0;
    }

    cout << "The total insurance premium is: Rs. " << surcharge << endl;

    return 0;
}
