
#include <iostream>
using namespace std;

int main()
{
    int n = 0, sum = 0;

    cout << "Enter numbers to get their sum, enter -1 to stop." << endl;

    
    do {
        sum += n;

        cout << "Enter a number: ";
        cin >> n;
        
     
    } while (n != -1);

    cout << endl << "Sum is: " << sum;

    return 0;
}
