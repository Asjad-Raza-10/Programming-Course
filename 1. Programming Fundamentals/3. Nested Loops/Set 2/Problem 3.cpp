
#include <iostream>
using namespace std;
int main()
{
	int n = 0, j = 0, k = 1, sum = j + k;

	cout << "Enter the limit for Fibonacci Series: ";
	cin >> n;

	cout << endl << "The Fibonacci series is: " << j << " " << k << " ";

	for (int i = 3; i <= n; i++)
	{
		cout << sum << " ";
		
		j = k;
		k = sum;
		sum = j + k;
	}

	return 0;
}