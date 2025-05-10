#include <iostream>
using namespace std;
int main()
{
    int arr[20] = { 0 }, size = 0, key = 0, i = 0, j = 0;

    cout << "Enter the array size (maximum 20): ";
    cin >> size;

    cout << "Enter " << size << " values: ";

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter a key: ";
    cin >> key;

    for (i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            cout << "The first occurance is on index: " << i;
            break;
        }

    }

    for (j = size-1; j > i-1; j--)
    {
        if (arr[j] == key)
        {
            cout << "The last occurance is on index: " << j;
            break;
        }

    }

    return 0;
}