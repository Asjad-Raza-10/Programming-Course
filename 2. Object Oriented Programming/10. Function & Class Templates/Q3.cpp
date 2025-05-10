#include <iostream>

using namespace std;

template<typename T>
class Matrix
{
private:
	T arr[3][3];
public:
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
};

int main()
{
	int M1[3][3] = { 1,2,3,4,5,6,7,8,9 };
	int M2[3][3] = { 1,2,3,4,5,6,7,8,9 };

	Matrix<int> Mat1(M1);
	Matrix<int> Mat2(M2);

	cout << endl << "Matrix 1: " << endl;
	Mat1.display();
	cout << endl << "Matrix 2: " << endl;
	Mat2.display();

	Matrix<int> Sum = Mat1 + Mat2;
	cout << endl << "Sum of Matrices: " << endl;
	Sum.display();

	return 0;
}