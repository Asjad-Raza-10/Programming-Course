#include <iostream>
using namespace std;

class Person
{
private:
	string name;
	unsigned int age;
	string id;
public:
	Person(string n = "", unsigned int a = 0, string i = "") :name(n), age(a), id(i) {}

	void displayInfo()
	{
		cout << "Person Name: " << name << endl << "Age: " << age << endl << "ID: " << id << endl;
	}
};

class Student : public Person
{
private:
	string Course;
	float CGPA;
public:
	Student(string n = "", unsigned int a = 0, string i = "", string c = "", float g = 0) :Person(n, a, i), Course(c), CGPA(g) {}

	bool isEligibleForScholarship()
	{
		if (CGPA > 3.7)
			return true;
		return false;
	}

	void displayProfile()
	{
		string s = "";
		
		if (isEligibleForScholarship())
			s = "Yes";
		else
			s = "No";

		cout << "--- Student Profile ---" << endl;
		Person::displayInfo();
		cout << "Course: " << Course << endl << "CGPA: " << CGPA << endl << "Scholarship Eligibility: " << s << endl;
	}
};

class Teacher : public Person
{
private:
	string Department;
	unsigned int Publications;
public:
	Teacher(string n = "", unsigned int a = 0, string i = "", string d = "", unsigned int p = 0) :Person(n, a, i), Department(d), Publications(p) {}

	bool isEligibleForPromotion()
	{
		if (Publications >= 5)
			return true;
		return false;
	}

	void displayProfile()
	{
		string s = "";

		if (isEligibleForPromotion())
			s = "Yes";
		else
			s = "No";

		cout << endl << "--- Teacher Profile ---" << endl;
		Person::displayInfo();
		cout << "Department: " << Department << endl << "Publications: " << Publications << endl << "Promotion Eligibility: " << s << endl;
	}
};

class Admin : public Person
{
private:
	string Designation;
	unsigned int YearsOfService;
public:
	Admin(string n = "", unsigned int a = 0, string i = "", string d = "", unsigned int y = 0) :Person(n, a, i), Designation(d), YearsOfService(y) {}

	bool isEligibleForRetirement()
	{
		if (YearsOfService >= 30)
			return true;
		return false;
	}

	void displayProfile()
	{
		string s = "";

		if (isEligibleForRetirement())
			s = "Yes";
		else
			s = "No";

		cout << endl << "--- Teacher Profile ---" << endl;
		Person::displayInfo();
		cout << "Designation: " << Designation << endl << "Years of Service: " << YearsOfService << endl << "Retirement Eligibility: " << s << endl;
	}
};

int main()
{
	Student S1("Asjad Raza", 18, "24L-0583", "BSCS", 3.94);
	Teacher T1("Dr. Fahad", 26, "TCH101", "Computer Science", 6);
	Admin A1("Mrs. Asma", 58, "ADM901", "HR Manager", 32);

	S1.displayProfile();
	T1.displayProfile();
	A1.displayProfile();

	return 0;
}