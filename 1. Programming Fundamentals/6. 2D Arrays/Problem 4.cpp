#include <iostream>
using namespace std;
int main()
{
	int matrix[100][100] = { 0 }, row, col, transpose[100][100] = { 0 }, trns_row, trns_col, i, j;

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

	trns_row = col;
	trns_col = row;

	for (i = 0; i < trns_row; i++)
	{
		for (j = 0; j < trns_col; j++)
		{
			transpose[i][j] = matrix[j][i];
		}
	}

	cout << "The transpose of the matrix is: " << endl;

	for (i = 0; i < trns_row; i++)
	{
		for (j = 0; j < trns_col; j++)
		{
			cout << transpose[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}