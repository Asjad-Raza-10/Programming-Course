#include <iostream>
using namespace std;

int countVowels(char * str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
		{
			count++;
		}
	}
	return count;
}

int main()
{
	char name[100] = { '\0' };
	
	cout << "Enter your name: ";
	cin.getline(name, 100);

	cout << endl << "The number of vowels in your name are: " << countVowels(name);
		
	return 0;
}