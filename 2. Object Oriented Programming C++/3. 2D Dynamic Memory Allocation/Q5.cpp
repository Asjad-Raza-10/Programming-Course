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

void output(int** m, int r, int c)
{
	cout << "The updated matrix is:" << endl;


	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

bool swap(int** &m, int r, int c)
{
	int s1 = 0, s2 = 0;
	cout << "Enter the 2 row numbers to swap:";
	cin >> s1 >> s2;

	if (s1 > (r-1) || s2 > (r-1) || s1 < 0 || s2 < 0)
	{
		cout << "Invalid row numbers!";
		return 1;
	}

	int* temp = m[s1];
	m[s1] = m[s2];
	m[s2] = temp;

	return 0;
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

	if (swap(matrix, r, c))
	{
		return 0;
	}
	
	output(matrix, r, c);

	deallocate(matrix, r);
	return 0;
}
