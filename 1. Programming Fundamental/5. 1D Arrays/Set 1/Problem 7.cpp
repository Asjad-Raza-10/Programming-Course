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

	int temp = arr[0];

	for (i = 0; i < size; i++)
	{
		arr[i]= arr[i+1];
	}

	arr[size - 1] = temp;

	cout << "The numbers shifted 1 place to left are: ";
	
	for (i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}