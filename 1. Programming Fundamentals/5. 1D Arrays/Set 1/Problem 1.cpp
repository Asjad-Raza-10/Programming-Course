#include <iostream>
using namespace std;
int main()
{
	int arr[20] = { 0 };
	int i = 0, p = 0, size = 0;

	cout << "Enter the maximum size of array: ";
	cin >> size;

	for (i = 0; i < size; i++)
	{
		cout << "Enter the position number where you want to store the value number " << (i + 1) << " : ";
		cin >> p;
		cout << "Enter value to store in poition " << p << " :";
		cin >> arr[p];
	}

	for (i = 0; i < size; i++)
	{
		cout << "The value stored in position " << i << " is: " << arr[i] << endl;
	}

	return 0;
}