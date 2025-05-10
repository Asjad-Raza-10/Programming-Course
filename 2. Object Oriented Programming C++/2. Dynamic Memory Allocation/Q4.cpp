#include <iostream>
using namespace std;

int* InsertValue(int* arr, int &size, int value, int index)
{
	int* ptra = new int[size];

	int i = 0;
	for (i = 0; i < index; i++)
	{
		ptra[i] = arr[i];
	}
	ptra[index] = value;
	
	for (i = index+1; i <= size; i++)
	{
		ptra[i] = arr[index++];
	}

	size++;
	return ptra;
}

int main()
{
	int size = 3, * arr = new int[size], value = 27, index = 2;
	
	for (int i = 0; i < size; i++)
	{
		arr[i] = (i+1) * 10;
	}
	
	int * ptr = InsertValue(arr, size, value, index);

	delete[]arr;
	arr = ptr;
	ptr = nullptr;

	cout << "The updated array after adding " << value << " at index " << index << " is: " << endl;

	

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	delete[]arr;
	arr = nullptr;

	return 0;
}