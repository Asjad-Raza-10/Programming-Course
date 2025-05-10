#include <iostream>
using namespace std;

class Department
{
private:
	string deptname;
	int stdcount;
	string hod;
public:
	Department(string d = "", int c = 0, string h = "")
	{
		deptname = d;
		stdcount = c;
		hod = h;
	}

	void setDeptName(string d)
	{
		deptname = d;
	}

	void setStdCount(int c)
	{
		stdcount = c;
	}

	void setHod(string h)
	{
		hod = h;
	}

	string getDeptName()
	{
		return deptname;
	}

	int getStdCount()
	{
		return stdcount;
	}

	string getHod()
	{
		return hod;
	}

	void increaseStdCount(int n)
	{
		stdcount += n;
	}
};

class University
{
private:
	string uniname;
	string location;
	Department department;
public:
	University(string n = "", string l = "", string d = "", int c = 0, string h = "") :department(d, c, h)
	{
		uniname = n;
		location = l;
	}

	void configureDepartment(string d = "", int c = 0, string h = "")
	{
		department.setDeptName(d);
		department.setStdCount(c);
		department.setHod(h);
	}

	void incrementStdCount(int n)
	{
		department.increaseStdCount(n);
	}

	void display()
	{
		cout << endl << "University Details:" << endl;
		cout << "University Name: " << uniname << endl;
		cout << "Location: " << location << endl;
		cout << "Department Name: " << department.getDeptName() << endl;
		cout << "Number of Students: " << department.getStdCount() << endl;
		cout << "Head of Department: " << department.getHod() << endl;
	}

};




int main()
{
	University FAST("National University of Computing and Emerging Sciences", "Pakistan", "Data Science", 800, "Dr. Kashif Zafar");
	FAST.display();

	cout << endl << "Configuring Department Details:" << endl;

	FAST.configureDepartment("Computer Science", 1200, "Dr. Aamir Wali");
	FAST.display();

	cout << endl << "Adding 400 more students:" << endl;
	FAST.incrementStdCount(400);

	FAST.display();

	return 0;
}