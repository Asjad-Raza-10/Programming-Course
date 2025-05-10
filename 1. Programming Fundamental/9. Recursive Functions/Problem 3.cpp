#include <iostream>
using namespace std;

int arr[100] = { 0 }, s = 0, i = 0;

int input_size(int s)
{
	cout << "Enter size of an array: ";
	cin >> s;
	
	return s;
}

void input_array(int arr[100], int s)
{
	cout << endl << "Enter " << s << " values: " << endl;
	for (int i = 0; i < s; i++)
	{
		cin >> arr[i];
	}
}

int max(int arr[100], int i, int s, int m)
{
	if (i < s)
	{
		if (arr[i] > m)
		{
			m = arr[i];
		}
		return max(arr, i + 1, s, m);
	}
	else
	{
		return m;
	}
}

int min(int arr[100], int i, int s, int m)
{
	if (i < s)
	{
		if (arr[i] < m)
		{
			m = arr[i];
		}
		return min(arr, i + 1, s, m);
	}
	else
	{
		return m;
	}
}

int main()
{
	s = input_size(s);
	input_array(arr, s);

	cout << "The maximum number is: " << max(arr, i, s, arr[0]) << endl;
	cout << "The minimum number is: " << min(arr, i, s, arr[0]);

	return 0;
}