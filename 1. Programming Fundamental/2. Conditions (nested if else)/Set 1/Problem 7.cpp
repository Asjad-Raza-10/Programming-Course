
#include <iostream>
using namespace std;

int main()
{
    char c;

    cout << "Enter an alphabet: ";
    cin >> c;

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
    {
        cout << "The alphabet is a vowel." << endl;
    }
    else
    {
        cout << "The alphabet is not a vowel." << endl;
    }

    cout << endl;
    return 0;
}
