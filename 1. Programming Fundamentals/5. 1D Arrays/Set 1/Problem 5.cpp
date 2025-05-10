#include <iostream>
using namespace std;

int main()
{
    int arr[20] = { 0 };
    int i = 0, size = 0;

    cout << "Enter size of array (maximum 20): ";
    cin >> size;

    if(size < 3)
	{
		cout<<"Cannot find multiples for size less than 3.";
		return 0;
	}
	
	cout << "Enter " << size << " numbers: ";
    
    for (i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    int temp_first = arr[0], temp_last = arr[size - 1];
    
    int arr_2[20];
    for (i = 0; i < size; i++) {
        arr_2[i] = arr[i];
    }
    
    
    for (i = 1; i < size - 1; i++)
    {    
        arr[i] = arr_2[i - 1] * arr_2[i + 1]; 
    }


    arr[0] = arr_2[size - 1] * arr_2[1];   
    arr[size - 1] = arr_2[0] * arr_2[size - 2];


    cout << "Updated array: ";
    for (i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
