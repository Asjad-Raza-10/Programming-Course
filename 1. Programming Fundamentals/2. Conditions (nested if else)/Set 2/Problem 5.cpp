#include <iostream>
using namespace std;

int main()
{
    int num = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, count = 0;

    cout << "Enter a 6 digit number: ";
    cin >> num;

    if (num / 1000000 != 0)
        cout << endl << "Enter a 6 digit number only";
    else
    {
        d1 = num / 100000;
        d2 = (num % 100000) / 10000;
        d3 = (num % 10000) / 1000;
        d4 = (num % 1000) / 100;
        d5 = (num % 100) / 10;
        d6 = num % 10;

        cout << endl << "The digits of the number are: " << d1 << ", " << d2 << ", " << d3 << ", " << d4 << ", " << d5 << ", " << d6 << ", ";
        cout << endl << endl;

        //Counting number of 0 digits
        if (d1 == 0)
            count++;
        if (d2 == 0)
            count++;
        if (d3 == 0)
            count++;
        if (d4 == 0)
            count++;
        if (d5 == 0)
            count++;
        if (d6 == 0)
            count++;
        cout << "Count of digit '0' in the number is: " << count << endl;
        count = 0;

        //Counting number of 1 digits
        if (d1 == 1)
            count++;
        if (d2 == 1)
            count++;
        if (d3 == 1)
            count++;
        if (d4 == 1)
            count++;
        if (d5 == 1)
            count++;
        if (d6 == 1)
            count++;
        cout << "Count of digit '1' in the number is: " << count << endl;
        count = 0;

        //Counting number of 2 digits
        if (d1 == 2)
            count++;
        if (d2 == 2)
            count++;
        if (d3 == 2)
            count++;
        if (d4 == 2)
            count++;
        if (d5 == 2)
            count++;
        if (d6 == 2)
            count++;
        cout << "Count of digit '2' in the number is: " << count << endl;
        count = 0;

        //Counting number of 3 digits
        if (d1 == 3)
            count++;
        if (d2 == 3)
            count++;
        if (d3 == 3)
            count++;
        if (d4 == 3)
            count++;
        if (d5 == 3)
            count++;
        if (d6 == 3)
            count++;
        cout << "Count of digit '3' in the number is: " << count << endl;
        count = 0;

        //Counting number of 4 digits
        if (d1 == 4)
            count++;
        if (d2 == 4)
            count++;
        if (d3 == 4)
            count++;
        if (d4 == 4)
            count++;
        if (d5 == 4)
            count++;
        if (d6 == 4)
            count++;
        cout << "Count of digit '4' in the number is: " << count << endl;
        count = 0;

        //Counting number of 5 digits
        if (d1 == 5)
            count++;
        if (d2 == 5)
            count++;
        if (d3 == 5)
            count++;
        if (d4 == 5)
            count++;
        if (d5 == 5)
            count++;
        if (d6 == 5)
            count++;
        cout << "Count of digit '5' in the number is: " << count << endl;
        count = 0;

        //Counting number of 6 digits
        if (d1 == 6)
            count++;
        if (d2 == 6)
            count++;
        if (d3 == 6)
            count++;
        if (d4 == 6)
            count++;
        if (d5 == 6)
            count++;
        if (d6 == 6)
            count++;
        cout << "Count of digit '6' in the number is: " << count << endl;
        count = 0;

        //Counting number of 7 digits
        if (d1 == 7)
            count++;
        if (d2 == 7)
            count++;
        if (d3 == 7)
            count++;
        if (d4 == 7)
            count++;
        if (d5 == 7)
            count++;
        if (d6 == 7)
            count++;
        cout << "Count of digit '7' in the number is: " << count << endl;
        count = 0;

        //Counting number of 8 digits
        if (d1 == 8)
            count++;
        if (d2 == 8)
            count++;
        if (d3 == 8)
            count++;
        if (d4 == 8)
            count++;
        if (d5 == 8)
            count++;
        if (d6 == 8)
            count++;
        cout << "Count of digit '8' in the number is: " << count << endl;
        count = 0;

        //Counting number of 9 digits
        if (d1 == 9)
            count++;
        if (d2 == 9)
            count++;
        if (d3 == 9)
            count++;
        if (d4 == 9)
            count++;
        if (d5 == 9)
            count++;
        if (d6 == 9)
            count++;
        cout << "Count of digit '9' in the number is: " << count << endl;
        count = 0;
    }


    cout << endl;
    return 0;
}