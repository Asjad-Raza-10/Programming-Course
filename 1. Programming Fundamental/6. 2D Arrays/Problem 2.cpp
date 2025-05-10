#include <iostream>
using namespace std;
int main()
{
	int mat_1[100][100] = { 0 }, mat_2[100][100] = { 0 }, row_1, col_1, row_2, col_2, result[100][100] = { 0 }, row_res, col_res, i, j;
	char operation;

	cout << "Enter number of rows for 1st matrix: ";
	cin >> row_1;

	cout << "Enter number of columns for 1st matrix: ";
	cin >> col_1;

	cout << "Enter values: " << endl;

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

	if (row_1 != col_1 || row_2 != col_2)
	{
		cout << "Matrices cannot be added or subtraced.";
		return 0;
	}

	cout << "Enter values: " << endl;

	for (i = 0; i < row_2; i++)
	{
		for (j = 0; j < col_2; j++)
		{
			cin >> mat_2[i][j];
		}
	}

	row_res = row_1;
	col_res = col_1;

	cout << "Choose operation, + or -: ";
	cin >> operation;

	if (operation == '+')
	{
		for (i = 0; i < row_res; i++)
		{
			for (j = 0; j < col_res; j++)
			{
				result[i][j] = mat_1[i][j] + mat_2[i][j];
			}
		}

		cout << "The sum of both matrices is: " << endl;

		for (i = 0; i < row_res; i++)
		{
			for (j = 0; j < col_res; j++)
			{
				cout << result[i][j] << " ";
			}
			cout << endl;
		}

		return 0;
	}

	else if (operation == '-')
	{

		for (i = 0; i < row_res; i++)
		{
			for (j = 0; j < col_res; j++)
			{
				result[i][j] = mat_1[i][j] - mat_2[i][j];
			}
		}

		cout << "The difference between both matrices is: " << endl;

		for (i = 0; i < row_res; i++)
		{
			for (j = 0; j < col_res; j++)
			{
				cout << result[i][j] << " ";
			}
			cout << endl;
		}

		return 0;
	}
	else
	{
		cout << "Choose + or - only.";
		return 0;
	}

}
	