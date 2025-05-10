#include <iostream>
using namespace std;

int* filterPrimes(const int* array, int size, int& primeCount)
{
	int* arr = new int[size];
	
	int i = 0;
	for (i = 0; i < size; i++)
	{
		bool flag = 1;
		for (int j = 2; j < array[i]; j++)
		{
			if (array[i] % j == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			arr[primeCount++] = array[i];
		}
	}

	int* ptr = new int[primeCount];
	for (i = 0; i < primeCount; i++)
	{
		ptr[i] = arr[i];
	}

	delete[]arr;
	arr = nullptr;
	return ptr;
}

int main()
{
	//hard-quoting input:
	int size = 11, primeCount = 0;
	int* array = new int[size]; 

	for (int i = 0; i < size; i++)
	{
		array[i] = i + 2;
	}

	int* PrimeNumbers = filterPrimes(array, size, primeCount);

	cout << "There are total " << primeCount << " Prime Numbers which are:" << endl;
	for (int i = 0; i < primeCount; i++)
	{
		cout << PrimeNumbers[i] << " ";
	}

	delete[]array;
	delete[]PrimeNumbers;

	array = nullptr;
	PrimeNumbers = nullptr;

	return 0;
}