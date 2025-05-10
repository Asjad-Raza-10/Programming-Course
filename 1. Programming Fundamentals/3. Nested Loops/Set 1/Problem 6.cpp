#include <iostream>
using namespace std;
int main()
{
	char c = 65;
	int i = 0, j = 0, k = 0, l = 0, repitions = 0;
	
	char temp = c;

	//printing first line only
	for (i = 0; i < 7; i++)
	{
		cout << temp << " ";
		temp += 1;
	}
	
	temp -= 1;
	
	for (i = 0; i < 6; i++)
	{
		temp -= 1;
		cout << temp << " ";
	}

	repitions += 1;
	cout << endl;
	
	//printing remaining lines
	for (i = 6; i >= 1; i--)
	{
		temp = c;
		for (j = 1; j <= i ; j++)
		{
			cout << temp << " ";
			temp += 1;
		}
		
		for (k = 0; k < repitions; k++)
		{
			cout << "  ";
		}
		for (l = i; l >= 1; l--)
		{
			temp -= 1;
			cout << temp << " ";
		}
		repitions += 2;
		cout << endl;
	}

	return 0;
}