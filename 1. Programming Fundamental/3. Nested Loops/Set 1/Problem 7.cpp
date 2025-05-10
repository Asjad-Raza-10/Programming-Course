#include <iostream>

using namespace std;

int main()
{
    float series = 0;
    for (int i = 1; i <= 7; i++)
    {
        int fact = 1;
        for (int j = i; j >= 1; j--)
        {
            fact *= j;
        }
        series += (float(i) / fact);
    }
    cout << "The value of the series is: " << series;

    return 0;
}