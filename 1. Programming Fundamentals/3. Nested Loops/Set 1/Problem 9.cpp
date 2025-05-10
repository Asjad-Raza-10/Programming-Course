#include <iostream>
using namespace std;
int main()
{
    int n = 0, digits = 0, check_sum = 0;
    
    cout << "Enter a number: ";
    cin >> n;

    if(n == 0)
    {
        cout << "0 is a special case of Armstrong number.";
        return 0;
    }
    else if(n < 0)
    {
        cout << "A negative number cannot be an armstrong number.";
        return 0;
    }

    int temp = n;

    while(temp != 0)
    {
        temp /= 10;
        digits++;
    }

    temp = n;
    
    while(temp != 0)
    {
        int temp_2 = temp % 10;
        check_sum += pow(temp_2,digits);   
        temp /= 10;     
    }

    if(check_sum == n)
    {
        cout << n << " is an Armstrong number.";
    }
    else
    {
        cout << "Not an Armstrong number.";
    }
    return 0;
}