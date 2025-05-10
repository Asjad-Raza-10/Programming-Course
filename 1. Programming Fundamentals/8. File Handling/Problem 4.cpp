#include <iostream>
#include <fstream>

using namespace std;

const int s = 4;

int arr[s][s], transpose[s][s];

void read()
{
	fstream input("data.txt", ios::in);

	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			input >> arr[i][j];
		}
	}

	input.close();
}

void trans(int arr[s][s])
{
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			transpose[i][j] = arr[j][i];
		}
	}
}

void disp(int arr[s][s])
{
	
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void store(int transpose[s][s])
{
	fstream output("data.txt", ios::out);
	{
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				output << transpose[i][j] << " ";
			}
			output << endl;
		}
	}
	output.close();
}

int main()
{
	read();
	cout << "The matrix from data.txt is: " << endl;

	disp(arr);

	trans(arr);
	store(transpose);

	cout << endl << "The transpose of the array is: " << endl;
	disp(transpose);

	return 0;
}