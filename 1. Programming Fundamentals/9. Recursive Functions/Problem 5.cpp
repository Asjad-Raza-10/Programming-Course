#include <iostream>
using namespace std;

char arr[100] = { '\0' };
int i = 0, flag = 1;

void input(char arr[100])
{
	cout << "Enter a string: ";
	cin.getline(arr, 100);
}

int find_size(char arr[100])
{
	int s = 0;
	while (arr[s] != '\0')
	{
		s++;
	}
	return s;
}

void check(char arr[100], int s, int i)
{
	if (i < s / 2)
	{
		if (arr[i] != arr[s - 1])
		{
			flag = 0;
		}

		return check(arr, (s - 1), i + 1);
	}
}

int main()
{
	input(arr);
	int s = find_size(arr);
	check(arr, s, i);

	if (flag == 1)
	{
		cout << "The string is a palindrome";
	}
	else
	{
		cout << "The string is not a palindrome";
	}
	return 0;
}