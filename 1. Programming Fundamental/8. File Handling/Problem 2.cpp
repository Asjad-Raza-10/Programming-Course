#include <iostream>
#include <fstream>

using namespace std;

void separate_even_odd()
{
	fstream numbers("numbers.txt", ios::in);
	fstream even("Even.txt", ios::out);
	fstream odd("Odd.txt", ios::out);
	
	int n = 0;
	while (numbers >> n)
	{
		if (n % 2 == 0)
		{
			even << n << endl;
		}
		else
		{
			odd << n << endl;
		}
	}
	numbers.close();
	even.close();
	odd.close();
}

int main()
{
	separate_even_odd();

	cout << endl << "Even and Odd numbers are separated!" << endl;

	return 0;
}