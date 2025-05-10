#include<iostream>
using namespace std;

class Student {

private:
	int rollno;
	string name;
	int marks[5];

public:
	Student() 
	{
		name = "Unknown";
		rollno = 0;
		for (int i = 0; i < 5; i++) 
		{
			marks[i] = 0;
		}
	}
	Student(string n, int r, int* m) 
	{
		name = n;
		rollno = r;
		for (int i = 0; i < 5; i++) 
		{
			marks[i] = m[i];
		}
	}
	int getTotalMarks() 
	{
		int totalMarks = 0;
		for (int i = 0; i < 5; i++) 
		{
			totalMarks += marks[i];
		}
		return totalMarks;
	}
	int getAvgMarks() 
	{
		return (float)getTotalMarks() / 5;
	}
	void displayDetails() 
	{
		cout << "Name: " << name << endl;
		cout << "Roll No: " << rollno << endl;
		cout << "Total Marks: " << getTotalMarks() << endl;
		cout << "Average Marks: " << getAvgMarks() << endl;
	}
};

int main() 
{
	int marks[5] = { 15,35,45,50,90 };
	Student S1("Asjad", 7680, marks);
	S1.displayDetails();

	cout << endl;
	Student S2;
	S2.displayDetails();

	return 0;
}