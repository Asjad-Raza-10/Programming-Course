#include <iostream>

using namespace std;

class Employee
{

public:
	virtual int calculateSalary() = 0;
	~Employee()
	{
		cout << "Employee Destructor Called" << endl;
	}
};

class SalariedEmployee :public Employee
{
private:
	int monthlysalary;
public:
	SalariedEmployee(int m = 0) : monthlysalary(m){}

	int calculateSalary() override
	{
		return monthlysalary;
	}

	~SalariedEmployee()
	{
		cout << "Salaried Employee Destructor Called" << endl;
	}
};

class HourlyEmployee :public Employee
{
private:
	int h_wage;
	int h_worked;
public:
	HourlyEmployee(int wg = 0, int wk = 0) : h_wage(wg), h_worked(wk) {}

	int calculateSalary() override
	{
		return (h_wage * h_worked);
	}

	~HourlyEmployee()
	{
		cout << "Hourly Employee Destructor Called" << endl;
	}
};


int main()
{	
	SalariedEmployee SE(5000);
	HourlyEmployee HE(100, 40);

	cout << "Hourley Employee Salary: " << HE.calculateSalary() << endl;
	cout << "Salaried Employee Salary: " << SE.calculateSalary() << endl;
	cout << "Total Salary: " << (SE.calculateSalary()+HE.calculateSalary()) << endl;


	return 0;
}