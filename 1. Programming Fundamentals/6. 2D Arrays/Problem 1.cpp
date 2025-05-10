#include <iostream>
using namespace std;
int main()
{
	int mat_1[100][100] = { 0 }, mat_2[100][100] = { 0 }, row_1, col_1, row_2, col_2, mul[100][100] = { 0 }, row_mul, col_mul, i, j, k, temp = 0;

	cout << "Enter number of rows for 1st matrix: ";
	cin >> row_1;

	cout << "Enter number of columns for 1st matrix: ";
	cin >> col_1;

	cout << "Enter values: ";

	for (i = 0; i < row_1; i++)
	{
		for (j = 0; j < col_1; j++)
		{
			cin >> mat_1[i][j];
		}
	}

	cout << "Enter number of rows for 2nd matrix: ";
	cin >> row_2;

	cout << "Enter number of columns for 2nd matrix: ";
	cin >> col_2;

	if (col_1 != row_2)
	{
		cout << "Matrices cannot be multiplied.";
		return 0;
	}

	cout << "Enter values: ";

	for (i = 0; i < row_2; i++)
	{
		for (j = 0; j < col_2; j++)
		{
			cin >> mat_2[i][j];
		}
	}

	row_mul = row_1;
	col_mul = col_2;


	for (i = 0; i < row_mul; i++)
	{
		for (j = 0; j < col_mul; j++)
		{
			temp = 0;
			for (k = 0; k < col_1; k++)
			{
				temp += (mat_1[i][k] * mat_2[k][j]);

			}
			mul[i][j] = temp;
		}
	}

	cout << "The multiple of both matrices is: ";
	
	for (i = 0; i < row_mul; i++)
	{
		for (j = 0; j < col_mul; j++)
		{
			cout << mul[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}