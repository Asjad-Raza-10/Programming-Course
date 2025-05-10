#include <iostream>
using namespace std;
int main()
{
	int arr[20] = { 0 }, size = 0, i = 0, j = 0, flag = 1, temp = 0, missing_number = 0;

	cout << "Enter the array size(maximum 20): ";
	cin >> size;

	cout << "Enter " << size << " values: ";
	for (i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	int arr_2[20] = { 0 };
	for (i = 0; i < size; i++)
	{
		arr_2[i] = i;
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 0;
			}
		}
		if (flag)
		{
			break;
		}
	}

	for (i = 0; i < size; i++)
	{
		if (arr[i] != arr_2[i])
		{
			missing_number = arr_2[i];
			break;
		}
	}

	cout << "The missing number is: " << missing_number;

	return 0;
}