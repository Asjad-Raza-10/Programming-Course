#include <iostream>
using namespace std;

class Student
{
private:
	string name;
	string roll_no;
public:
	Student(string n = "", string r = "") :name(n), roll_no(r) {}

	void displayInfo()
	{
		cout << endl << "Student Name: " << name << endl << "Roll Number: " << roll_no << endl;
	}
};

class OOPStudent : public Student
{
private:
	float lab_marks;
	float theory_marks;
public:
	OOPStudent(string n = "", string r = "", float l = 0.0, float t = 0.0) :Student(n, r), lab_marks(l), theory_marks(t) {}

	float calculateTotal()
	{
		return (lab_marks + theory_marks);
	}

	void displayResult()
	{
		Student::displayInfo();
		cout << "OOP Lab Marks: " << lab_marks << endl << "OOP Theory Marks: " << theory_marks << endl << "Total Marks: " << calculateTotal() << endl;
	}
};

int main()
{
	OOPStudent A1("Asjad Raza", "24L-0583", 98, 92);

	A1.displayResult();

	return 0;
}