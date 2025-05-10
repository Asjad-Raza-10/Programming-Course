#include <iostream>
using namespace std;

int mat_1[100][100] = { 0 }, mat_2[100][100] = { 0 }, row_1, col_1, row_2, col_2, mul[100][100] = { 0 }, row_mul, col_mul, i, j, k, temp = 0;

int input_row_1(int row_1)
{
	cout << "Enter number of rows for 1st matrix: ";
	cin >> row_1;
	return row_1;
}

int input_col_1(int col_1)
{
	cout << "Enter number of columns for 1st matrix: ";
	cin >> col_1;
	return col_1;
}

int input_row_2(int row_2)
{
	cout << "Enter number of rows for 2nd matrix: ";
	cin >> row_2;
	return row_2;
}

int input_col_2(int col_2)
{
	cout << "Enter number of columns for 2nd matrix: ";
	cin >> col_2;
	return col_2;
}

int check(int col_1, int row_2)
{
	if (col_1 != row_2)
	{
		cout << endl << "Matrices cannot be multiplied.";
		return 1;
	}
	else
		return 0;
}

void input_1(int row_1, int col_1, int mat_1[100][100])
{

	cout << "Enter values for 1st matrix: " << endl;

	for (i = 0; i < row_1; i++)
	{
		for (j = 0; j < col_1; j++)
		{
			cin >> mat_1[i][j];
		}
	}
}

void input_2(int row_2, int col_2, int mat_2[100][100])
{
	cout << "Enter values for 2nd matrix: " << endl;
	for (i = 0; i < row_2; i++)
	{
		for (j = 0; j < col_2; j++)
		{
			cin >> mat_2[i][j];
		}
	}

}


void mult(int row_1, int col_2, int mat_1[100][100], int mat_2[100][100])
{
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
}

void disp(int row_mul, int col_mul, int mul[100][100])
{
	cout << "The multiple of both matrices is: ";

	for (i = 0; i < row_mul; i++)
	{
		for (j = 0; j < col_mul; j++)
		{
			cout << mul[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	row_1 = input_row_1(row_1);
	col_1 = input_col_1(col_1);
	row_2 = input_row_2(row_2);
	col_2 = input_col_2(col_2);

	temp = check(col_1, row_2);

	if (temp == 1)
	{
		return 0;
	}

	input_1(row_1, col_1, mat_1);
	input_2(row_2, col_2, mat_2);
	

	mult(row_1, col_2, mat_1, mat_2);
	disp(row_mul, col_mul, mul);

	return 0;
}