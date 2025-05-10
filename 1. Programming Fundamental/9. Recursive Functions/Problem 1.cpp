#include <iostream>
using namespace std;

int input(int n)
{
	cout << "Enter the term number: ";
	cin >> n;

	return n;
}

int fibonacci(int n)
{
	if (n <= 1)
	{
		return n;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
	int n = 0;

	n = input(n) - 1;

	cout << "The " << n+1 << "th term is: " << fibonacci(n);

	return 0;
}