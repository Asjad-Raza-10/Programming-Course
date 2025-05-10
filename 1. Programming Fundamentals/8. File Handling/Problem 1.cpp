#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int name_size = 7;
char rec_1[name_size][name_size], rec_2[name_size][name_size];

void read_data(char rec_1[][name_size], char rec_2[][name_size])
{
	ifstream read1("record_1.txt");
	ifstream read2("record_2.txt");

	if (!read1 || !read2) 
	{
		cout << "Error opening files!" << endl;
		return;
	}
	
	int i = 0;

	while (i < name_size && read1.getline(rec_1[i], name_size)) 
	{
		i++;
	}

	i = 0;

	while (i < name_size && read2.getline(rec_2[i], name_size)) 
	{
		i++;
	}

	read1.close();
	read2.close();
}

void disp(char arr[][name_size])
{
	for (int i = 0; i < name_size; i++)
	{
		cout << arr[i] << endl;
	}
}

bool is_unique(char element[], char array[][name_size], int size)
{

	for (int i = 0; i < size; i++) 
	{
		if (strcmp(element, array[i]) == 0) 
		{
			return false;  
		}
	}
	return true;  
}

void unique_elements(char rec_1[][name_size], char rec_2[][name_size])
{
	ofstream output("Output.txt", ios::app);

	if (!output) 
	{
		cout << "Error opening output file!" << endl;
		return;
	}

	cout << endl << "Unique elements:" << endl;


	for (int i = 0; i < name_size; i++) 
	{
		if (is_unique(rec_1[i], rec_1, i) && is_unique(rec_1[i], rec_2, name_size)) 
		{
			output << rec_1[i] << endl;
			cout << rec_1[i] << endl; 
		}
	}


	for (int i = 0; i < name_size; i++) 
	{
		if (is_unique(rec_2[i], rec_2, i) && is_unique(rec_2[i], rec_1, name_size)) 
		{
			output << rec_2[i] << endl;
			cout << rec_2[i] << endl; 
		}
	}

	output.close();
}

int main()
{
	read_data(rec_1, rec_2);

	cout << endl << "The contents of record 1 are: " << endl;
	disp(rec_1);

	cout << endl << "The contents of record 2 are: " << endl;
	disp(rec_2);

	unique_elements(rec_1, rec_2);

	cout << endl << "Unique elements written to Output.txt" << endl;

	return 0;
}