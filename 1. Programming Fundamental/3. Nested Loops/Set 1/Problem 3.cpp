#include <iostream>
using namespace std;

int main()
{
    char s = 1;
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 119; j++)
            cout << s;
        cout << endl;
    }
    return 0;
}