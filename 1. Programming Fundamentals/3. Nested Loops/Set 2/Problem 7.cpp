
#include <iostream>
using namespace std;

int main() 
{
	int n = 0, m = 0, product = 0;

	cout << "Enter a number: ";
	cin >> n;

	if (n < 0)
	{
		cout << endl << "Do not enter a negative number.";
		return 0;
	}

	cout << "Enter a number to multiply with " << n << ": ";
	cin >> m;

	if (m < 0)
	{
		cout << endl << "Do not enter a negative number.";
		return 0;
	}


	for (int i = n; i > 0; i--)
	{
		product += m;
	}

	cout << "The product of " << n << " and " << m << " is: " << product;

	return 0;
}