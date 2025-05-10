#include <iostream>
using namespace std;
int main()
{
	int arr_1[20] = { 0 }, arr_2[20] = { 0 }, size = 0, size_1 = 0, size_2 = 0, i = 0, j = 0, k = 0;

	//Input first set
	cout << "Enter the size of first array (maximum 20): ";
	cin >> size_1;

	cout << "Enter " << size_1 << " values: ";
	for (i = 0; i < size_1; i++)
	{
		cin >> arr_1[i];
	}

	//Check for duplicate values in first set
	for (i = 0; i < size_1; i++)
	{
		for (j = 0; j < size_1; j++)
		{
			if (i != j)
			{
				if (arr_1[i] == arr_1[j])
				{
					cout << "No duplicate elements are allowed.";
					return 0;
				}
			}
		}
	}

	//Input second set
	cout << endl << "Enter the size of second array (maximum 20): ";
	cin >> size_2;

	cout << "Enter " << size_2 << " values: ";
	for (i = 0; i < size_2; i++)
	{
		cin >> arr_2[i];
	}

	//Check for duplicate values in second set
	for (i = 0; i < size_2; i++)
	{
		for (j = 0; j < size_2; j++)
		{
			if (i != j)
			{
				if (arr_2[i] == arr_2[j])
				{
					cout << "No duplicate elements are allowed.";
					return 0;
				}
			}
		}
	}


	if (size_1 > size_2)
		size = size_1;
	else
		size = size_2;


	cout << endl << endl;

	//output array 1
	cout << "Array 1: ";
	for (i = 0; i < size_1; i++)
	{
		cout << arr_1[i] << " ";
	}

	cout << endl;

	//output array 2
	cout << "Array 2: ";
	for (i = 0; i < size_2; i++)
	{
		cout << arr_2[i] << " ";
	}
	cout << endl << endl;

	//finding intersection
	int intersection[20] = { 0 };
	int intersection_size = 0;
	k = 0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (arr_1[i] == arr_2[j])
			{
				intersection[k] = arr_1[i];
				k++;
			}
		}
	}

	intersection_size = k;
	k = 0;

	cout << "The intersection of array 1 and array 2 is: ";

	for (i = 0; i < intersection_size; i++)
	{
		cout << intersection[i] << " ";
	}

	cout << endl;

	//finding difference
	int difference[20] = { 0 };
	int difference_size = 0;
	k = 0;
	int temp[20] = { 0 };

	for (i = 0; i < size; i++)
	{
		if (arr_2[i] != intersection[i])
		{
			difference[k] = arr_2[i];
			k++;
		}
	}


	difference_size = k;
	k = 0;

	cout << "The difference between array 2 and array 1 is: ";

	for (i = 0; i < difference_size; i++)
	{
		cout << difference[i] << " ";
	}

	cout << endl;

	//finding union
	int array_union[20] = { 0 };
	int union_size = 0;
	k = 0;

	for (i = 0; i < size_1; i++)
	{
		array_union[i] = arr_1[i];
		k++;
	}

	for (i = 0; i <= difference_size; i++)
	{
		array_union[k+i] = difference[i];
		k++;
	}

	union_size = k;

	cout << "The union of array 1 and array 2 is: ";

	for (i = 0; i < union_size; i++)
	{
		cout << array_union[i] << " ";
	}


	return 0;
}