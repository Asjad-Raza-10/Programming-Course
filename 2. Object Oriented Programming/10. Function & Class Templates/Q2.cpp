#include <iostream>

using namespace std;

template<typename T>
T findMax(T* arr, int size)
{
	T max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

template<typename T>
void display(T* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ", ";
	}
}

int main()
{
	int int_arr[5] = {10, 20, 5, 40, 25};
	float float_arr[4] = {3.25, 6.57, 1.95, 7.82};
	string string_arr[4] = {"Apple", "Banana", "Grape", "Mango"};

	cout << endl << "Integer Array: "; display<int>(int_arr, 5);
	cout << endl << "Float Array: "; display<float>(float_arr, 4);
	cout << endl << "String Array: "; display<string>(string_arr, 4);

	cout << endl;

	cout << endl << "Max in Integer Array: " << findMax<int>(int_arr, 5);
	cout << endl << "Max in Float Array: " << findMax<float>(float_arr, 4);
	cout << endl << "Max in String Array: " << findMax<string>(string_arr, 4) << endl;

	return 0;
}