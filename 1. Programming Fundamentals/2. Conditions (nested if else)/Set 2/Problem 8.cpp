#include <iostream>
using namespace std;

int main()
{
    float income = 0.0;
    cout << "Enter your monthly income";
    cin >> income;
    cout << endl;

    if (income < 0.0)
        cout << "You are going farther into dept every month";
    else if (income < 1200.00)
        cout << "You are living below the poverty line";
    else if (income < 2500)
        cout << "You are living in moderate comfort";
    else
        cout << "You are well off";


    cout << endl;
    return 0;
}
