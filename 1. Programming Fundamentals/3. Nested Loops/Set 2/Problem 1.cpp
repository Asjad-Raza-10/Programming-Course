#include <iostream>
using namespace std;

int main()
{
	int n = 0, fact = 1;

	cout << "Enter a number to get its factorial ";
	cin >> n;

	for (int i = n; i > 0; i--)
	{
		fact = fact * i;
	}

	cout << "The factorial of " << n << " is " << fact;

	return 0;
}