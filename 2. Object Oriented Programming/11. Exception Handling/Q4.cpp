#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class FileNotOpeningException : public exception
{
  public:
	const char *what() const noexcept override
	{
		return "Error: Unable to open the file.";
	}
};

class InvalidNameException : public exception
{
  public:
	const char *what() const noexcept override
	{
		return "Error: Name cannot be empty.";
	}
};

class InvalidRollNoException : public exception
{
  public:
	const char *what() const noexcept override
	{
		return "Error: Roll number cannot be negative.";
	}
};

class InvalidNumberException : public exception
{
  public:
	const char *what() const noexcept override
	{
		return "Error: Marks cannot be negative.";
	}
};

class StudentRecords
{
  public:
	void add(string name, int roll_no, float marks)
	{
		if (name.empty())
			throw InvalidNameException();

		if (roll_no < 0)
			throw InvalidRollNoException();

		if (marks < 0)
			throw InvalidNumberException();

		fstream file("StudentRecord.txt", ios::out | ios::app);
		if (!file)
			throw FileNotOpeningException();

		file << roll_no << " " << name << " " << marks << endl;
		file.close();
	}
};

int main()
{
	StudentRecords r;

	try
	{
		r.add("Ahmad Ali", 240349, 38);
		r.add("Hamza Ayub", 225671, 29);
		r.add("Zaeem Ahmed", 202277, 46);
		r.add("", 2123, 30); // to test error
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}

	cout << "Records added successfully." << endl;
	return 0;
}
