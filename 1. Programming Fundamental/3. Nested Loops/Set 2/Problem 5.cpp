#include <iostream>
using namespace std;
int main()
{
	int n = 0, r = 0;

	cout << "Enter a number: ";
	cin >> n;


	cout << "The number in reverse order is: ";

	for (int i = n; i >= 0; i--)
	{
		r = n % 10;
		cout << r;

		n /= 10;
		i /= 10;
	}


	return 0;
}