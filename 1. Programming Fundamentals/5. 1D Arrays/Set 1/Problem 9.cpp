#include <iostream>
using namespace std;
int main()
{
	int arr_org[20] = { 0 }, arr_swap[20] = { 0 }, arr_new[20] = { 0 };
	int i = 0, size = 0, count = 0;

	cout << "Enter size of array (maximum 20): ";
	cin >> size;

	cout << "Enter " << size << " numbers: ";

	for (i = 0; i < size; i++)
	{
		cin >> arr_org[i];
	}

	for (i = 0; i<size; i++)
	{
		arr_swap[i] = arr_org[i];
	}

	for (int r = 0; r < size; r++)
	{
		int temp = arr_swap[0];

		for (i = 0; i < size; i++)
		{
			arr_swap[i] = arr_swap[i + 1];
		}

		arr_swap[size - 1] = temp;

		cout << "The array after left shift " << (r + 1) << " times is: ";
		
		for (i = 0; i < size; i++)
		{
			cout << arr_swap[i] << " ";
		}

		cout << endl;

		arr_new[r] = arr_swap[size - 1];

		cout << "The value of the third array is: ";
		for (int k = 0; k <= r; k++)
		{
			cout << arr_new[k] << " ";
		}

		cout << endl;

		count++;
	}

	cout << endl << "The array will be same after " << count << " left iterations.";

	return 0;
}