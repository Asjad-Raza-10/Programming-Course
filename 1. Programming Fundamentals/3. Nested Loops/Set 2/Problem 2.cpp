
#include <iostream>
using namespace std;
int main()
{
	int a = 0, b = 0, max = 0, min = 0;

	cout << "Enter a number: ";
	cin >> a;

	cout << "Enter another number: ";
	cin >> b;

	if (a > b)
	{
		max = a;
		min = b;
	}
	else
	{
		max = b;
		min = a;
	}

	while (min != max)
	{
		if (max > min)
			max -= min;
		else
			min -= max;
	}

	cout << "GCD of " << a << " and " << b << " is " << max;

	return 0;
}