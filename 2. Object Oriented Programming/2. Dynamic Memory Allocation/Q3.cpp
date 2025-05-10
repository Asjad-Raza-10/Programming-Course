#include <iostream>
using namespace std;

int* prefixSum(const int* arr, const int size)
{
	int* ptr = new int[size];
	
	int sum = 0, * p_ptr = ptr;
	const int* p_arr = arr;

	for (int i = 0; i < size; i++)
	{
		sum += *(p_arr++);
		*(p_ptr++) = sum;
	}

	return ptr;
}

int main()
{
	int size = 5, * arr = new int[size];
	
	for (int i = 0; i < size; i++)
	{
		arr[i] = i + 1;
	}

	int* PrefixSumArray = prefixSum(arr, size);

	cout << "The array with prefix sum is: " << endl;

	for (int i = 0; i < size; i++)
	{
		cout << PrefixSumArray[i] << " ";
	}

	delete[]arr;
	delete[]PrefixSumArray;
	arr = nullptr;
	PrefixSumArray = nullptr;

	return 0;
}