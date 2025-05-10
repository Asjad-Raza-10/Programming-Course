#include<iostream>
using namespace std;

int main()
{
	int num1=0;

	cout << "Enter a number:" << endl;
	cin >> num1;
	// get number from user 
	
	cout << "The number is now 0" << endl;

	num1 = 0;
	cout << "Number is =" << num1 << endl;
	cout << "and number is= " << num1++ << endl;
	cout << "After increment " << ++num1 << endl;
	cout << "at the end= " << num1 << endl;

	num1 = 10;
	cout << "Number is =" << num1 << endl;
	cout << "and number is= " << num1-- << endl;
	cout << "After increment " << --num1 << endl;
	cout << "at the end= " << num1;

	return 0;
	system("pause");
}