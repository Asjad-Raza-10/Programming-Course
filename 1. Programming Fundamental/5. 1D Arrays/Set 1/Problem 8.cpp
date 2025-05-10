#include <iostream>
using namespace std;
int main()
{
	int arr[20] = { 0 };
	int i = 0, size = 0;

	cout << "Enter size of array (maximum 20): ";
	cin >> size;

	cout << "Enter " << size << " numbers: ";

	for (i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	int flag = 1;

	for (i = 0; i < size/2; i++)
	{
		if (arr[i] != arr[size - i - 1])
		{
			flag = 0;
		}
	}

	if (flag == 1)
	{
		cout << "Array is a palindrome.";
	}
	else
	{
		cout << "Array is not a palindrome.";
	}

	return 0;
}