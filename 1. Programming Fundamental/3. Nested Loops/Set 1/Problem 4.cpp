#include <iostream>
using namespace std;
int main()
{
	int i = 0, j = 0, k = 0;

	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 3; j++)
		{

			for (k = 1; k <= 3; k++)
			{
				cout << i << j << k << endl;
			}
		}
	}
	return 0;
}