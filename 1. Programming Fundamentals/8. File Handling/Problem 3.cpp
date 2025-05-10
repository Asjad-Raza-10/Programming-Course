#include <iostream>
#include <fstream>

using namespace std;

fstream input("input.txt", ios::in);

int menu(int n)
{
	cout << "1. Encrypt Data" << endl << "2. Decrypt Data";
	cout << endl << "Enter your choice: ";
	cin >> n;
	if (n != 1 && n != 2)
	{
		cout << "Enter a valid choice!" << endl;
	}
	else
	{
		return n;
	}
}

void encrypt()
{
	fstream encrypt("encrypted.txt", ios::out);

	char temp[100] = { NULL };

	while (!input.eof())
	{
		input.getline(temp, 100);
	}

	for (int i = 0; temp[i] != '\0'; i++)
	{
		temp[i]++;
	}
	
	encrypt << temp;

	cout << "The encrypted data is: " << temp << endl;
	
	input.close();
	encrypt.close();
}

void decrypt()
{
	fstream decrypt("decrypted.txt", ios::out);

	char temp[100] = { NULL };

	while (!input.eof())
	{
		input.getline(temp, 100);
	}

	for (int i = 0; temp[i] != '\0'; i++)
	{
		temp[i]--;
	}

	decrypt << temp;

	cout << "The decrypted data is: " << temp << endl;

	input.close();
	decrypt.close();
}
int main()
{
	int n = 0;

	n = menu(n);

	if (n == 1)
	{
		encrypt();
	}
	else if (n == 2)
	{
		decrypt();
	}

	return 0;
}