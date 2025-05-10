#include <iostream>

using namespace std;

template<typename T>
class Matrix
{
private:
	T arr[3][3];
public:
	Matrix()
	{}

	Matrix(T M[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				arr[i][j] = M[i][j];
			}
		}
	}

	Matrix operator+(const Matrix& M)
	{
		T Sum[3][3];

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Sum[i][j] = arr[i][j] + M.arr[i][j];
			}
		}
		return Sum;
	}

	void display()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	Matrix& transpose()
	{
		Matrix resultant;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				resultant.arr[i][j] = arr[j][i];
			}
		}
		return resultant;
	}


	T get(int i, int j)
	{
		if (i >= 3 || j >= 3)
		{
			return -1;
		}
		else
		{
			return arr[i][j];
		}
	}
};

int main()
{
	int M1[3][3] = { 1,2,3,4,5,6,7,8,9 };
	int M2[3][3] = { 1,2,3,4,5,6,7,8,9 };

	Matrix<int> Mat1(M1);
	Matrix<int> Mat2(M2);

	cout << endl << "Matrix 1: " << endl;
	Mat1.display();

	Matrix<int> Transpose = Mat1.transpose();
	cout << endl << "Transpose of Matrice: " << endl;
	Transpose.display();

	int i, j;
	cout << "Enter index for element( , ): " << endl;
	cin >> i >> j;
	if (Mat1.get(i, j) != -1)
	{
		cout << "Accessing element at (" << i << ", " << j << "): " << (Mat1.get(i, j)) << endl;
	}
	else
	{
		cout << "Accessing element at (" << i << ", " << j << "): Index out of bound error." << endl;
	}

	return 0;
}