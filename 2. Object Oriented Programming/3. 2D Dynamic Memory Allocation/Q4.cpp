#include <iostream>

using namespace std;

bool input(int**& m, int& r, int& c)
{
	cout << "Enter number of rows: ";
	cin >> r;
	cout << "Enter number of columns: ";
	cin >> c;

	if (r < 1 || c < 1)
	{
		cout << "Invalid sizes!";
		return 1;
	}

	m = new int* [r];

	for (int i = 0; i < r; i++)
	{
		m[i] = new int[c];
	}

	cout << "Enter values for matrix:" << endl;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cin >> m[i][j];
		}
	}
	return 0;
}

void output(int* m, int s)
{
	cout << "Column Sums = [ ";

		for (int i = 0; i < s; i++)
		{
			cout << m[i] << ", ";
		}
	cout << "]";
}

int* columnSums(int** m, int r, int c)
{
	int* sum = new int[c];
	
	for (int i = 0; i < c; i++)
	{
		sum[i] = 0;
		for (int j = 0; j < r; j++)
		{
			sum[i] += m[j][i];
		}
	}

	return sum;
}

void deallocate(int**& m, int r)
{
	for (int i = 0; i < r; i++)
	{
		delete[]m[i];
	}
	delete[]m;
}

int main()
{
	int** matrix, r = 0, c = 0;

	if (input(matrix, r, c))
	{
		return 0;
	}
	int size = c;
	int* column_sums = columnSums(matrix, r, c);
	output(column_sums, size);

	deallocate(matrix, r);
	delete[]column_sums;
	
	return 0;
}
