#include <iostream>
using namespace std;

int main() 
{
    int arr[20] = { 0 };
    int size = 0;

    cout << "Enter the size of the array (maximum 20): ";
    cin >> size;

    cout << "Enter " << size << " numbers: ";
    for (int i = 0; i < size; i++)
	{
        cin >> arr[i];
    }

    int most_frequent = arr[0];  
    int max_count = 0;           

    for (int i = 0; i < size; i++) 
	{
        int count = 0;

        for (int j = 0; j < size; j++) 
		{
            if (arr[i] == arr[j]) 
			{
                count++;
            }
        }

        if (count > max_count)
		{
            max_count = count;
            most_frequent = arr[i];
        }
    }

    cout << "The most frequent element is: " << most_frequent << endl;

    return 0;
}
