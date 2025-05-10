
#include <iostream>
using namespace std;
int main() {

	float miles=0.0, gallons=0.0, mileage=0.0;
	
	cout << "Enter the number of miles travelled: \t";
	cin >> miles;

	cout << endl << "Enter the number of gallons filled: \t";
	cin >> gallons;

	mileage = miles / gallons;

	cout << endl << "Your car's mileage is: \t\t\t" << mileage << " miles per gallons" << endl << endl;

	return 0;
}
