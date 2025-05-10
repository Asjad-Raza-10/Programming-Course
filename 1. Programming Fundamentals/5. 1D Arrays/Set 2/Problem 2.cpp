#include <iostream>
using namespace std;
int main()
{
    int arr[20] = { 0 }, size = 0, i = 0;

    cout << "Enter the array size (maximum 20): ";
    cin >> size;

    cout << "Enter " << size << " values: ";

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    int arr_copy[20] = { 0 };

    for (i = 0; i < size; i++)
    {
        arr_copy[i] = arr[i];

    }

    cout << "The copied array is: ";

    for (i = 0; i < size; i++)
    {
        cout << arr_copy[i] << " ";

    }

    return 0;
}