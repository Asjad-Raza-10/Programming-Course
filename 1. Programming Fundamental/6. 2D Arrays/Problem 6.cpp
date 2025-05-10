#include <iostream>
using namespace std;
int main()
{
	char string[100] = { NULL };

	cout << "Enter a string: ";
	cin.getline(string, 100);

	int i = 0, flag = 1, count = 0;

	while (string[i] != NULL)
	{
		i++;
	}

	count = i-1;


	for (i = 0; i < (count/2); i++)
	{
		if (string[i] != string[count - i])
		{
			flag = 0;
			break;
		}
	}

	if (flag == 1)
	{
		cout << "String is a palindrome.";
	}
	else
	{
		cout << "String is not a palindrome.";
	}


	return 0;
}