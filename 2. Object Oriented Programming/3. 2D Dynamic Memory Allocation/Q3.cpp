#include <iostream>
#include <cstring>

using namespace std;

bool input(int** &m, int &r, int &c)
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

void output(int** m, int r, int c)
{
	cout << "The transpose matrix is:" << endl;


	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

int** transposeMatrix(int** m, const int r, const int c)
{
	int** transpose_m = new int* [c];

	for (int i = 0; i < c; i++)
	{
		transpose_m[i] = new int[r];
	}

	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			transpose_m[i][j] = m[j][i];
		}
	}

	delete[]m;
	return transpose_m;
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

	matrix = transposeMatrix(matrix, r, c);

	output(matrix, r, c);

	deallocate(matrix, r);
	return 0;
}
