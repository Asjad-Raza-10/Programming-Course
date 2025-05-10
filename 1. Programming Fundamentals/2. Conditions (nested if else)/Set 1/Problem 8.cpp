#include <iostream>
using namespace std;

int main()
{
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n7 = 0, n8 = 0, n9 = 0, n10 = 0;
    int sum = 0;
    int above_avg = 0, below_avg = 0;
    float average = 0.0;

    cout << "Enter 10 numbers: " << endl;
    cin >> n1 >> n2 >> n3 >> n4 >> n5 >> n6 >> n7 >> n8 >> n9 >> n10;

    sum = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9 + n10;

    average = sum / 10.0;

    cout << endl << "Average of the numbers: " << average << endl <<endl;

    if (n1 > average)
        {
            cout << n1 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n1 << " is below average." << endl;
            below_avg++;
        }

    if (n2 > average)
        {
            cout << n2 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n2 << " is below average." << endl;
            below_avg++;
        }

    if (n3 > average)
        {
            cout << n3 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n3 << " is below average." << endl;
            below_avg++;
        }

    if (n4 > average)
        {
            cout << n4 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n4 << " is below average." << endl;
            below_avg++;
        }

    if (n5 > average)
        {
            cout << n5 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n5 << " is below average." << endl;
            below_avg++;
        }

    if (n6 > average)
        {
            cout << n6 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n6 << " is below average." << endl;
            below_avg++;
        }

    if (n7 > average)
        {
            cout << n7 << " is above average." << endl;
            above_avg++;
        }
    else
        cout << n7 << " is below average." << endl;
        below_avg++;

    if (n8 > average)
        {
            cout << n8 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n8 << " is below average." << endl;
            below_avg++;
        }

    if (n9 > average)
        {
            cout << n9 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n9 << " is below average." << endl;
            below_avg++;
        }

    if (n10 > average)
        {
            cout << n10 << " is above average." << endl;
            above_avg++;
        }
    else
        {
            cout << n10 << " is below average." << endl;
            below_avg++;
        }


    cout << endl << endl << above_avg << " numbers are above average and " << below_avg << " numbers are below average.";
    cout << endl;
    return 0;
}
