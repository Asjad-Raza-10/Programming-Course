#include <iostream>
using namespace std;

class Person
{
private:
	string name;
	unsigned int age;
public:
	Person(string n = "", unsigned int a = 0) :name(n), age(a) {}

	string getName()
	{
		return name;
	}

	unsigned int getAge()
	{
		return age;
	}

	void setName(string n)
	{
		name = n;
	}

	void setAge(unsigned int a)
	{
		age = a;
	}

};

class Lecturer : public Person
{
private:
	string LecturerID;
	unsigned int BasePay;
public:
	Lecturer(string n = "", unsigned int a = 0, string id = "", unsigned int p = 0) :Person(n, a), LecturerID(id), BasePay(p) {}

	string getLecturerID()
	{
		return LecturerID;
	}
	
	unsigned int getBasePay()
	{
		return BasePay;
	}

	void setLecturerID(string s)
	{
		LecturerID = s;
	}

	void setBasePay(unsigned int a)
	{
		BasePay = a;
	}
};

class SeniorLecturer : public Lecturer
{
private:
	float BonusPercent;
	unsigned int NumberOfCourses;
public:
	SeniorLecturer(string n = "", unsigned int a = 0, string id = "", unsigned int p = 0, float bp = 0, unsigned int noc = 0) :Lecturer(n, a, id, p), BonusPercent(bp), NumberOfCourses(noc) {}

	float getBonusPercent()
	{
		return BonusPercent;
	}

	float getBonusPay()
	{
		return (BonusPercent * getBasePay());
	}

	unsigned int getNumberOfCourses()
	{
		return NumberOfCourses;
	}

	void setBonusPercent(float bp)
	{
		BonusPercent = bp;
	}

	void setNumberOfCourses(unsigned int noc)
	{
		NumberOfCourses = noc;
	}
};

class CourseLead: public SeniorLecturer
{
private:
	unsigned int ActiveCourses;
	float CourseRatings;
public:
	CourseLead(string n = "", unsigned int a = 0, string id = "", unsigned int p = 0, float bp = 0, unsigned int noc = 0, unsigned int ac = 0, float cr = 0) :SeniorLecturer(n, a, id, p, bp, noc), ActiveCourses(ac), CourseRatings(cr) {}

	float CalculateTotalPay()
	{
		return (getBasePay() + getBonusPay());
	}

	bool CheckPerformance()
	{
		if (ActiveCourses > 5 && CourseRatings > 4.5)
			return true;
		return false;
	}

	float getCourseRatings()
	{
		return CourseRatings;
	}

	unsigned int getActiveCourses()
	{
		return ActiveCourses;
	}

	void setCourseRatings(float cr)
	{
		CourseRatings = cr;
	}

	void setActiveCourses(unsigned int ac)
	{
		ActiveCourses = ac;
	}
};


int main()
{
	CourseLead CL("Asjad Raza", 18, "24L-0583", 50000, 0.2, 12, 7, 4.94);

	cout << endl << "Instructor Details: " << endl << "Name: " << CL.getName() << endl << "Age: " << CL.getAge() << endl << "Instructor ID: " << CL.getLecturerID() << endl << "Base Pay: " << CL.getBasePay() << endl << "Bonus Percentage: " << CL.getBonusPercent() << endl << "Number of Courses: " << CL.getNumberOfCourses() << endl;
	cout << endl << "Total Pay Calculation: " << endl << "Base Pay: " << CL.getBasePay() << endl << "Bonus (" << (CL.getBonusPercent() * 100) << "%): " << CL.getBonusPay() << endl << "Total Pay: " << CL.CalculateTotalPay() << endl;
	cout << endl << "Performance Evaluation: " << endl << "Active Courses: " << CL.getActiveCourses() << endl << "Course Rating: " << CL.getCourseRatings() << endl << "Instructor Performance: " << (CL.CheckPerformance() ? "Top Performering Instructor" : "Not Top Performering Instructor") << endl;
	return 0;
}