#include <iostream>
using namespace std;

void range(int& x, int& y)
{
    cout << "Enter the start of the range: ";
    cin >> x;

    cout << "Enter the end of the range: ";
    cin >> y;
}

bool is_prime(int a, int b)
{
    if (a <= 1)
    {
        return 0;
    }
    if (b == 1)
    {
        return 1;
    }
    if (a % b == 0)
    {
        return 0;
    }
    return is_prime(a, b - 1);
}

int sum_p(int x, int y)
{
    if (x <= y)
    {
        if (is_prime(x, x - 1))
        {
            return x + sum_p(x + 1, y);
        }
        return sum_p(x + 1, y);
    }
    else
    {
        return 0;
    }
}

int main()
{
    int x = 0, y = 0;

    range(x, y);

    cout << "The sum of all prime numbers within the range is: " << sum_p(x, y) << endl; // Added newline

    return 0;
}
