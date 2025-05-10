#include <iostream>
using namespace std;

int main()
{
    float weight = 0.0, calories = 0.0;
    char lifestyle = ' ';

    cout << "Enter your weight (in kg): ";
    cin >> weight;

    if (weight < 0)
    {
        cout << "Invalid Weight";
        return 0;
    }

    cout << "Enter your lifestyle (A for active, S for sedentary): ";
    cin >> lifestyle;

    if (lifestyle == 'A' || lifestyle == 'a')
    {
        calories = weight * 15;
    }
    else if (lifestyle == 'S' || lifestyle == 's')
    {
        calories = weight * 13;
    }
    else
    {
        cout << "Invalid input for lifestyle." << endl;
        return 0;
    }

    cout << "The recommended daily calorie intake is: " << calories << " calories." << endl;

    return 0;
}
