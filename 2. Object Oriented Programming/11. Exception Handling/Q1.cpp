#include <iostream>

using namespace std;

class Student
{
  private:
	int marks[5];

  public:
	Student()
	{
		for (int i = 0; i < 5; i++)
		{
			marks[i] = 0;
		}
	}

	void setMarks(int m)
	{
		static int index = 0;

		if (m < 0 || m > 100)
		{
			throw "InvalidMarkException";
		}
		marks[(index++) % 5] = m;
	}

	double getAverage()
	{
		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum += marks[i];
		}
		return sum / 5.0;
	}

	void display()
	{
		cout << "--- Student Marks ---" << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << "Subject " << i + 1 << ": " << marks[i] << endl;
		}
		cout << "Average Marks: " << getAverage();
	}
};
int main()
{
	Student Asjad;
	int n = 0;

	cout << "Enter Marks for Subject 1 to 5. " << endl;

	for (int i = 0; i < 5; i++)
	{
		try
		{
			cout << "Enter Marks for Subject " << i + 1 << ": ";
			cin >> n;
			Asjad.setMarks(n);
		}
		catch (const char *msg)
		{
			cout << msg << ": Invalid input: Marks must be between 0 and 100." << endl;
			i--;
		}
	}

	Asjad.display();
	return 0;
}