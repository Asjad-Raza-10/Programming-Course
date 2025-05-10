#include <iostream>
using namespace std;

int main()
{
	int a = 0, b = 0, c = 0;

	cout << "Enter number 1: ";
	cin >> a;
	cout << endl << "Enter number 2: ";
	cin >> b;
	cout << endl << "Enter number 3: ";
	cin >> c;

	cout << endl << "The entered numbers are: " << a << ", " << b << ", " << c;

	cout << endl << "The sorted ascending order is: ";

	if (a < b && a < c)
		if (b < c)
			cout << a << ", " << b << ", " << c;
		else
			cout << a << ", " << c << ", " << b;
	else if (b < a && b < c)
		if (a < c)
			cout << b << ", " << a << ", " << c;
		else
			cout << b << ", " << c << ", " << a;
	else
		if (a < b)
			cout << c << ", " << a << ", " << b;
		else
			cout << c << ", " << b << ", " << a;

	
	cout << endl;
	return 0;
}
