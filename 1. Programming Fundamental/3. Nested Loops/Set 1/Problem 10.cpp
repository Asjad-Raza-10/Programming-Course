#include <iostream>
using namespace std;
int main()
{
	int num1 = 0, num2 = 0, LCM = 0, GCD = 0, greater = 0, smaller = 0;

	cout << "Enter a number: ";
	cin >> num1;

	cout << "Enter another number: ";
	cin >> num2;

	if (num1 > num2)
	{
		greater = num1;
		smaller = num2;
	}
	else
	{
		greater = num2;
		smaller = num1;
	}
		
	int temp = greater;

	while (temp % smaller != 0)
	{
		temp += greater;
	}

	LCM = temp;

	GCD = (num1 * num2) / LCM;

	cout << "LCM of both numbers is: " << LCM << endl;
	cout << "GCD of both numbers is: " << GCD;

	return 0;
}