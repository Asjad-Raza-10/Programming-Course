#include <iostream>

using namespace std;

template<typename T>
class Calculator
{
private:
	T a;
	T b;
public:
	Calculator(T x = 0, T y = 0) : a(x), b(y) {}

	T sum()
	{
		return a + b;
	}

	T diff()
	{
		return a - b;
	}

	T product()
	{
		return a * b;
	}

	T division()
	{
		return a / b;
	}
};

int main()
{
	int a, b;
	cout << "Input 2 numbers:" << endl;
	cout << "First Number: ";
	cin >> a;
	cout << "Second Number: ";
	cin >> b;

	Calculator<int> C((int)a, (int)b);
	cout << endl << "Results: " << endl;
	cout << "Addition: " << C.sum() << endl;
	cout << "Subtraction: " << C.diff() << endl;
	cout << "Multiplication: " << C.product() << endl;
	cout << "Division: " << C.division() << endl;

	return 0;
}