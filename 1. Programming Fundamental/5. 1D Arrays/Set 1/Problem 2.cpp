#include <iostream>
using namespace std;
int main()
{
	int arr[20] = { 0 };
	int i = 0, j = 0;

	cout << "How many values do you want to store in the array? (maximum size 20): ";
	cin >> i;

	cout << "Enter " << i << " values: ";

	for (int j = 0; j < i; j++)
	{
		cin >> arr[j];
	}

	int smallest = arr[0], smallest_position = 0;

	for (j = 0; j < i; j++)
	{
		if (arr[j] < smallest)
		{
			smallest = arr[j];
			smallest_position = j;
		}
	}

	int second_smallest = 0;

	for (j = 0; j < i; j++)
	{
		if (arr[j] != smallest)
		{
			second_smallest = arr[j];
		}
	}


	for (j = 0; j < i; j++)
	{
		if (j == smallest_position)
		{
			continue;
		}
		if (arr[j] < second_smallest)
		{
			second_smallest = arr[j];
		}

	}

	cout << "The second smallest number is: " << second_smallest;
	return 0;
}