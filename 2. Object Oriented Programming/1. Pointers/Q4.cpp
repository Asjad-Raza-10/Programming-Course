#include <iostream>
using namespace std;

int* SecondLargestElement(int* arr, int size, int *num)
{
	int largest = *arr;

	for (int i = 0; i < size; i++)
	{
		if (*(arr+i) > largest)
		{
			largest = *(arr+i);
		}
	}

	int SecondLargest = *arr;

	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	for (int i = 0; i < size; i++)
	{
		if (*(arr+i) != largest)
		{
			if (*(arr+i) > SecondLargest)
			{
				SecondLargest = *(arr+i);
			}
		}
	}

	*num = SecondLargest;

	int* ptr = &SecondLargest;
	return ptr;
}

int main()
{
	int size = 0, arr[5] = { 0 };

	cout << "Enter array size: ";
	cin >> size;

	cout << "Enter " << size << " values: ";

	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	int num = 0;
	int* ptr = SecondLargestElement(arr, size, &num);

	cout << endl << "The second largest element is " << num << " at address [" << ptr << "]";
	
	return 0;
}