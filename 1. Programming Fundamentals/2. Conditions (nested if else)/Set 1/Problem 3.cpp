#include <iostream>
using namespace std;

int main()
{
    int date = 0, month = 0, year = 0;

    cout << "Enter the year: ";
    cin >> year;

    cout << "Enter the month number: ";
    cin >> month;

    cout << "Enter the date: ";
    cin >> date;

    // General validation for invalid month or date
    if (date > 31 || date < 1 || month > 12 || month < 1)
    {
        cout << "Invalid Date" << endl;
        return 0;
    }

    // Handling February
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // leap year
        {
            if (date > 29)
            {
                cout << "Invalid Date" << endl;
                return 0;
            }
            else if (date == 29)
            {
                date = 1;
                month++;
            }
            else
            {
                date++;
            }
        }
        else // non-leap year
        {
            if (date > 28)
            {
                cout << "Invalid Date" << endl;
                return 0;
            }
            else if (date == 28)
            {
                date = 1;
                month++;
            }
            else
            {
                date++;
            }
        }
    }
    // Handling months with 30 days: April, June, September, November
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (date > 30)
        {
            cout << "Invalid Date" << endl;
            return 0;
        }
        else if (date == 30)
        {
            date = 1;
            month++;
        }
        else
        {
            date++;
        }
    }
    // Handling December separately for year increment
    else if (month == 12)
    {
        if (date > 31)
        {
            cout << "Invalid Date" << endl;
            return 0;
        }
        else if (date == 31)
        {
            date = 1;
            month = 1;
            year++;
        }
        else
        {
            date++;
        }
    }
    // Handling months with 31 days: January, March, May, July, August, October
    else
    {
        if (date > 31)
        {
            cout << "Invalid Date" << endl;
            return 0;
        }
        else if (date == 31)
        {
            date = 1;
            month++;
        }
        else
        {
            date++;
        }
    }

    cout << "The next date DD/MM/YYYY is: " << date << "/" << month << "/" << year << endl;
    return 0;
}
