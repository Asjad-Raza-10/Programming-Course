#include <iostream>
using namespace std;

void update(int& x)
{
	int* first_ptr = &x;
	int** second_ptr = &first_ptr;

	**second_ptr = 45;
}


int main()
{
	int x = 25;

	cout << "X = " << x;
	update(x);
	cout << endl << "X = " << x;


	return 0;
}
