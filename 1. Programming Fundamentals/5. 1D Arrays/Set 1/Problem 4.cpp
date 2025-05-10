#include <iostream>
using namespace std;
int main()
{
	int arr[20] = { 0 };
	int size = 0, i = 0;

	cout << "Enter size of the array (maximum 20): ";
	cin >> size;

	cout << "Enter " << size << " values: ";
	
	for (i = 0; i < size; i++)
	{
		cin >> arr[i];
	}
	
	int mid = -1;
	if ((size % 2) != 0)
	{
		mid = (size / 2) + 1;
	}

	int extra = 0;

	for (i = 0; i < (size/2); i++)
	{
		if (i == mid)
		{
			continue;
		}
		extra = arr[i];
		int f = size - i - 1;
		arr[i] = arr[f];
		arr[f] = extra;
	}

	cout << "The reversed array is: ";

	for (i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}