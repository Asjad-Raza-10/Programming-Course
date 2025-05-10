#include <iostream>
using namespace std;

int main()
{
	int n = 0;

	cout << "Enter the number of rows: ";
	cin >> n;

	cout << endl << endl;

	if (n <= 10)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = i; j <= n; j++)
			{
				cout << " ";
			}
			for (int k = 1; k <= i; k++)
			{
				cout << "* ";
			}
			cout << endl;
		}

	}
	else
	{
		cout << "Number of rows cannot be greater than 10.";
	}

	return 0;
}