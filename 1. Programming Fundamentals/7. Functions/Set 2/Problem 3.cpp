#include <iostream>
using namespace std;

int get_size(int size)
{
	cout << "Enter size of the series: ";
	cin >> size;
	return size;
}

void fibonacci(int size)
{
	int n1 = 0, n2 = 1, sum = n1 + n2;

	cout << endl << "Fibonacci Sequence = " << n1 << " " << n2 << " ";
	
	for (int i = 0; i < size; i++)
	{
		cout << sum << " ";
		n1 = n2;
		n2 = sum;
		sum = n1 + n2;
	}
}

int main()
{
	int size = 0;
	size = get_size(size);
	fibonacci(size);

	cout << endl;

	return 0;
}