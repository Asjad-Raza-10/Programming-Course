#include <iostream>
using namespace std;
int main()
{
	char string[100] = { '\0' }, new_string[100] = "", i = 0, j = 0, size = 0, space = 0, count = 0;

	cout << "Enter a string: ";
	cin.getline(string, 30);

	bool flag = 0;

	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == ' ')
		{
			count++;
		}
		if (count >= 2)
		{
			cout << "Enter two word name only.";
			return 0;
		}
	}

	for (i = 0; string[i] != '\0'; i++)
	{
		if (flag)
		{
			new_string[j] = string[i];
			j++;
		}
		if (string[i] == ' ')
		{
			flag = 1;
		}
	}

	new_string[j] = ' ';
	j++;

	for (i = 0; string[i] != ' '; i++)
	{
		new_string[j++] = string[i];
	}

	cout << "New string is: " << new_string;


	return 0;
}