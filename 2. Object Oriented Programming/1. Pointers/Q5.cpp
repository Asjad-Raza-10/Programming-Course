#include <iostream>
#include<string>

using namespace std;

void reverseArray(char* arr)
{
	int size = 0;

	while (arr[size] != '\0')
	{
		size++;
	}

	char temp = '\0';
	for (int i = 0; i < size / 2; i++)
	{
		temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}
}

int main()
{
	char arr[6] = { 0 };

	cout << "Enter a string (maximum 100): ";

	cin.getline(arr, 100);

	reverseArray(arr);

	cout << endl << "The reversed array is: ";
	for (int i = 0; arr[i] != '\0'; i++)
	{
		cout << arr[i];
	}

	return 0;
}