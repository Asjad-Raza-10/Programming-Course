
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int choice = 0;

	cout << "List of all Problems:" << endl << endl;
	
	cout << "Problem 2:  Guessing a Number" << endl;
	cout << "Problem 3:  Displaying Next Date" << endl;
	cout << "Problem 4:  Displaying Age Category" << endl;
	cout << "Problem 5:  Displaying Integer Type" << endl;
	cout << "Problem 6:  Checking Multiples" << endl;
	cout << "Problem 7:  Checking vowels" << endl;
	cout << "Problem 8:  Displaying Average and comparing numbers with average" << endl;
	cout << "Problem 9:  Auto Insurance Program" << endl;
	cout << "Problem 10: Calories Recommendation" << endl << endl;

	cout << "Enter the problem number you want the program for: ";
	cin >> choice;

	if (choice == 2)
		system("./'A2 Problem 2'");
    else if (choice == 3)
    {
        system("./'A2 Problem 3'");
    }
    else if (choice == 4)
    {
        system("./'A2 Problem 4'");
    }
    else if (choice == 5)
    {
        system("./'A2 Problem 5'");
    }
    else if (choice == 6)
    {
        system("./'A2 Problem 6'");
    }
    else if (choice == 7)
    {
        system("./'A2 Problem 7'");
    }
    else if (choice == 8)
    {
        system("./'A2 Problem 8'");
    }
    else if (choice == 9)
    {
        system("./'A2 Problem 9'");
    }
    else if (choice == 10)
    {
        system("./'A2 Problem 10'");
    }
    else
    {
        cout << "Invalid choice. Please enter a number between 1 and 10." << endl;
    }




	cout << endl;
	return 0;
}