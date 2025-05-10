#include <iostream>
using namespace std;
int main()
{
	int matrix[100][100] = { 0 }, row, col, sum = 0, i,j;

	cout << "Enter number of rows for matrix: ";
	cin >> row;
	cout << "Enter number of columns for matrix: ";
	cin >> col;

	cout << "Enter values: ";
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> matrix[i][j];
		}
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			sum += matrix[j][i];
		}
		cout << "Sum of column " << i + 1 << " is: " << sum << endl;
		sum = 0;
	}

	return 0;
}