
#include <iostream>
using namespace std;
int main()
{
	int n = 0, sum = 0, k = 0;

	cout << "Enter a number: ";
	cin >> n;

	for (int i = n; i > 0; i--)
	{
		k = n % 10;
		sum += k;
		n /= 10;
	}

	cout << "Sum of its digits is: " << sum;

	return 0;
}
