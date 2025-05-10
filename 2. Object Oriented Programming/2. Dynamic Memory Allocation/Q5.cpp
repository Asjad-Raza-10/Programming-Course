#include <iostream>
using namespace std;

void toUpperCase(char*string)
{
	char * ptr = string;
	while (*(ptr) != '\0')
	{
		if (*ptr >= 'a' && *ptr <= 'z')
		{
			*ptr -= ' ';
		}
		ptr++;
	}
}

int main()
{
	int size = 50;
	char* string = new char[size];
	cout << "Enter a string: ";
	cin.getline(string, size);
	
	toUpperCase(string);

	cout << "Updated String: " << string;

	delete[]string;
	string = nullptr;
	return 0;
}