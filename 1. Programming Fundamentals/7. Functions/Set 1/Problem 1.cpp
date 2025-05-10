#include <iostream>
using namespace std;
int main()
{
	int a = 0, b = 0, c = 0, GCD = 0;

	cout << "Enter 1st number: ";
	cin >> a;

	cout << "Enter 2nd number: ";
	cin >> b;

	cout << "Enter 3rd number: ";
	cin >> c;

	if (a < b)
	{
		if (a < c)
		{
			GCD = a;
		}
		else
		{
			GCD = c;
		}
	}
	else
	{
		if (b < c)
		{
			GCD = b;
		}
		else
		{
			GCD = c;
		}
	}

	int i = GCD;

	for (i; i > 0; i--)
	{
		if (a % i == 0 && b % i == 0 && c % i == 0)
		{
			GCD = i;
			break;
		}
	}


	cout << endl << "The GCD of the three numbers is: " << GCD;



	return 0;
}