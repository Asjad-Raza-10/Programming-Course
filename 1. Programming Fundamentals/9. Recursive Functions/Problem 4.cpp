#include <iostream>
using namespace std;

char arr[100] = { '\0' };
int i = 0;

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

void reverse(char arr[100], int s, int i)
{
	if (i < s/2)
	{
		char temp = arr[i];
		arr[i] = arr[s - 1];
		arr[s - 1] = temp;

		return reverse(arr, (s-1), i + 1);
	}
}

int main()
{
	input(arr);
	int s = find_size(arr);
	reverse(arr, s, i);

	cout << "The reversed string is: " << arr;

	return 0;
}