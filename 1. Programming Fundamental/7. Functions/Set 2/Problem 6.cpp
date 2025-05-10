#include <iostream>
using namespace std;

int i = 0;

int input(int n)
{
	cout << "Enter an positive integer to convert it into binary: ";
	cin >> n;
	return n;
}

void to_binary(int n, int arr[100])
{
	i = 0;

	while(n >= 0)
	{
		if (n != 1 && n != 0)
		{
			arr[i] = n % 2;
			i++;
		}
		else if (n == 1)
		{
			arr[i] = n;
		}
		else if (n == 0)
		{
			break;
		}
		n /= 2;
	}
}

void disp(int arr[100], int i)
{
	cout << endl << "The binary of the number is:" << endl;
	for (int k = i; k >= 0; k--)
	{
		cout << arr[k];
	}
}

int main()
{
	int n = 0, arr[100] = { 0 }, binary[100] = { 0 };
	n = input(n);
	to_binary(n, arr);
	disp(arr, i);

	return 0;
}
