#include <iostream>
using namespace std;
int main()
{
	int n = 0, rev_n = 0, d = 0;

	cout << "Enter a number: ";
	cin >> n;

	int k = n;

	while (k != 0)
	{
		d = k % 10;
		rev_n = ((rev_n) * 10) + d;

		k /= 10;
	}

	cout << endl << "Reversed Number: " << rev_n << endl << endl;
	
	if (n == rev_n)
	{
		cout << n << " is a palindrome number.";
	}
	else
	{
		cout << n << " is not a palindrome number.";
	}

	return 0;
}