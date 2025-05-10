#include <iostream>
using namespace std;

char arr[100] = { '\0' };
int n = 0;

void input(char arr[100])
{
	cout << "Enter a string: ";
	cin.getline(arr, 100);
}

char check(char arr[100])
{
	if (arr[n] >= 65 && arr[n] <= 90)
	{
		return arr[n];
	}
	else
	{
		n = n + 1;
		return check(arr);
	}
}

int main()
{
	input(arr);

	if (check(arr) != '\0')
	{
		cout << "The first uppercase character is: " << check(arr);
	}
	else
	{
		cout << "No uppercase letter";
	}
	return 0;
}