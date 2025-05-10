#include <iostream>
using namespace std;
int main()
{
	int matrix[100][100] = { 0 }, row, col, flag = 1, i, j;

	cout << "Enter number of rows for matrix: ";
	cin >> row;
	cout << "Enter number of columns for matrix: ";
	cin >> col;

	cout << "Enter values: " << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> matrix[i][j];
		}
	}

	for (i = 0; i < row; i++)
	{
		if (flag == 0)
		{
			break;
		}

		for (j = 0; j < col; j++)
		{
			if (i == j)
			{
				if (matrix[i][j] != 1)
				{
					flag = 0;
					break;
				}
				
			}
			else if (matrix[i][j] != 0)
			{
				flag = 0;
				break;
			}
		}
	}

	if (flag)
	{
		cout << "Identity Matrix.";
	}
	else
	{
		cout << "Not an Identity Matrix.";
	}


	return 0;
}