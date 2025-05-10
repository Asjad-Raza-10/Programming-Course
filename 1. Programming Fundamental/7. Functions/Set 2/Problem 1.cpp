#include <iostream>
using namespace std;

int matrix[100][100] = { 0 }, row, col, transpose[100][100] = { 0 }, trns_row, trns_col, i, j;

int input_row(int row)
{
	cout << "Enter number of rows for matrix: ";
	cin >> row;
	return row;
}

int input_col(int col)
{
	cout << "Enter number of columns for matrix: ";
	cin >> col;
	return col;
}

void input_values(int row, int col, int matrix[100][100])
{
	cout << "Enter values: " << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> matrix[i][j];
		}
	}
}

void trans(int row, int col, int transpose[100][100])
{
	trns_row = col;
	trns_col = row;

	for (i = 0; i < trns_row; i++)
	{
		for (j = 0; j < trns_col; j++)
		{
			transpose[i][j] = matrix[j][i];
		}
	}
}

void disp(int col, int row, int transpose[100][100])
{
	cout << "The transpose of the matrix is: " << endl;

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			cout << transpose[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	row = input_row(row);
	col = input_col(col);
	input_values(row, col, matrix);
	trans(row, col, transpose);
	disp(col, row, transpose);


	return 0;
}