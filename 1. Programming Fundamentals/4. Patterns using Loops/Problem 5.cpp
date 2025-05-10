#include <iostream>
using namespace std;
int main()
{
	int n = 0;
	int j = 0, repition=0;

	cout << "Enter the height of the pattern: ";
	cin >> n;

	if (n > 9 || n < 1)
	{
		cout << "The height cannot be 0, negative, or greater than 9.";
		return 0;
	}

	//Printing the first line only.

	for (int i = 1; i <= n; i++)
	{
		cout << i << " ";
	}
	for (int i = (n - 1); i >= 1; i--)
	{
		cout << i << " ";
	}

	cout << endl;

	//printing the remaining lines.
	
	n -= 1;

	for (int i = n; i >= 1; i--)
	{
		for (j = 1; j <= i; j++) //letft triangle of numbers
		{
			cout << j << " ";
		}
	
		for (int z = 0; z <= repition ; z++) //spaces
		{
			cout << "  ";
		}

		for (j = i; j >= 1; j--) //right triangle of numbers
		{
			cout << j << " ";
		}


		repition += 2;
		cout << endl;
	}
		cout << endl;





	return 0;
}