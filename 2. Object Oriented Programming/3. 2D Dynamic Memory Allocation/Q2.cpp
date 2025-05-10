#include <iostream>
#include <cstring>

using namespace std;

bool isVowel(char c)
{
	if (c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U' && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
	{
		return false;
	}
	return true;
}

void removeVowels(char** str)
{	
	int i = 0, size = 0;
	while ((*str)[i] != '\0')
	{
		if (!isVowel((*str)[i]))
		{
			size++;
		}
		i++;
	}

	char* copy = new char[size];

	int j = 0;

	for (i = 0; ((*str))[i] != '\0'; i++)
	{
		if(!isVowel((*str)[i]))
		{
			copy[j++] = (*str)[i];
		}
	}

	copy[j] = '\0';
	
	delete[]*str;
	*str = copy;
}


int main()
{
	char* str = new char[100];
	cout << "Enter a string: ";
	cin.getline(str, 100);

	removeVowels(&str);

	cout << "String without wovels is: " << str;

	delete[]str;
	return 0;
}
