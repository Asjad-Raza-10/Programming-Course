#include <iostream>
using namespace std;
int main()
{
    int n = 0, length = 0;

    cout << "Enter a number to print its Collatz sequence: ";
    cin >> n;

    if(n == 1)
    {
        cout << "There is no Collatz sequence for 1.";
        return 0;
    }
    else if (n == 0)
    {
        cout << "There is no Collatz sequence for 0.";
        return 0;
    }
    else if (n < 0)
    {
        cout << "There is no Collatz sequence for negative numbers.";
        return 0;
    }

    while(n >= 1)
    {
        cout << n << " -> ";

        if(n == 1)
        {
            length++;
            break;
        }

        if(n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n *= 3;
            n++;
        }

        length++;
    }

    cout << "length: " << length;


    return 0;
}