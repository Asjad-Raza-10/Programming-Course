#include <iostream>
using namespace std;

const int length = 100;

int arr_size(int vsize)
{
	cout << "Enter the length of the array, max 100" << endl;
	cin >> vsize;
	return vsize;
}

int input(int arr[], int vsize, int k)
{
	cout << "Enter the array:" << endl;
	for (int i = 0; i < vsize; i++)
	{
		cin >> arr[i];
	}

	cout << "Which kth largest element do you want to find?" << endl;
	cin >> k;
	return k;
}

void sort(int arr[], int vsize)
{
	int temp = 0;
	for (int i = 0; i < vsize - 1; i++)
	{
		for (int j = 0; j < vsize; j++)
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
	}
}

void largest(int arr[], int vsize, int k)
{
	cout << "The " << k << "th largest value = " << arr[k - 1] << endl;
}

int main()
{
	int vsize = 0, arr[length] = { 0 }, k = 0;
	vsize = arr_size(vsize);
	k = input(arr, vsize, k);
	sort(arr, vsize);
	largest(arr, vsize, k);

	system("pause");
	return 0;
}