#include <iostream>
using namespace std;
int main()
{
	char str[30] = "";

	cout << "Enter a string: ";
	cin.getline(str, 30);

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 32;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}

	cout << "New string is: " << str;


	return 0;
}