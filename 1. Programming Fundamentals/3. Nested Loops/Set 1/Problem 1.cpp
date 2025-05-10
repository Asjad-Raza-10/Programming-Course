#include <iostream>
using namespace std;
int main()
{
	int i = 0, j = 0, k = 0, temp = 0;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5-i; j++)
		{
			cout << "  ";
		}
		temp = 1;
		cout << temp;
		for (k = 1; k <= i; k++)
		{
			temp = (temp * (i - k + 1)) / k;
			cout << "   " << temp;
		}
		cout << endl;
	}

	return 0;
}