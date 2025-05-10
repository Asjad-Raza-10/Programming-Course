#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 0, b = 0, c = 0, sum = 0;
	float avg = 0;

	cout << "Enter first number:" << endl;
	cin >> a;

	cout << "Enter second number:" << endl;
	cin >> b;

	cout << "Enter third number:" << endl;
	cin >> c;

	sum = a + b + c;
	avg = (float)sum / 3;

	cout << "The sum of " << a << ", " << b << " and " << c << " = " << sum << endl;
	cout << "The average of " << a << ", " << b << " and " << c << " = " << avg << endl;

	cout << endl;
	system("pause");
	return 0;
}