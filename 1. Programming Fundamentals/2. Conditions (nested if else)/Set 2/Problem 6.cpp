#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0, c = 0;

	cout << "Enter 3 digits in descending order: ";
	cin >> a >> b >> c;



	if (a > b && b > c)
		cout << "In order";
	else
		cout << "Not in order";


    cout << endl;
    return 0;
}
