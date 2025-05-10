#include <iostream>
using namespace std;

int main()
{
    int age = 0;

    cout << "Enter the age: ";
    cin >> age;

    if (age < 0)
    {
        cout << "Invalid age!" << endl;
    }
    else if (age <= 2)
    {
        cout << "This person is a baby." << endl;
    }
    else if (age <= 4)
    {
        cout << "This person is a toddler." << endl;
    }
    else if (age <= 12)
    {
        cout << "This person is a child." << endl;
    }
    else if (age <= 19)
    {
        cout << "This person is a teenager." << endl;
    }
    else if (age <= 65)
    {
        cout << "This person is an adult." << endl;
    }
    else
    {
        cout << "This person is an old codger." << endl;
    }

    cout << endl;
    return 0;
}
