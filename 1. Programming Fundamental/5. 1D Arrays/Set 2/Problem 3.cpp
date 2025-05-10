#include <iostream>
using namespace std;
int main()
{
	int arr[20] = { 0 }, size = 0, i = 0, temp = 0, j = 0;

	cout << "Enter the array size(maximum 20): ";
	cin >> size;

	cout << "Enter " << size << " values: ";
	for (i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	bool flag = 1;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size-i-1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				flag = 0;
			}
		}
		if (flag)
		{
			break;
		}
	}

	cout << "The array in ascending order is: ";
	for (i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}