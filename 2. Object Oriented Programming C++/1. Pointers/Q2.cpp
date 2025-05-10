#include <iostream>
using namespace std;

void reverseArray(int* arr, int size)
{
	int temp = 0;
	for (int i = 0; i < size/2; i++)
	{
		temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}
}

int main()
{
	int size = 0;

	cout << "Enter array size (maximum 6): ";
	cin >> size;

	if (size > 6)
	{
		cout << "Size must be less than 6";
		return 0;
	}

	int arr[6] = { 0 };

	cout << "Enter " << size << " values: ";

	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	reverseArray(arr, size);

	cout << endl << "The reversed array is: ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}