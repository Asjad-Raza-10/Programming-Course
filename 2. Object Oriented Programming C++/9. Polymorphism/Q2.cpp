#include <iostream>

using namespace std;

class Report
{
public:
	virtual void generateReport()
	{
		cout << "Generating Base Report" << endl;
	}

	virtual ~Report()
	{
		cout << "Base Report Destructor Called" << endl;
	}
};

class SalesReport :public Report
{
public:
	
	void generateReport() override
	{
		cout << "Generating Sales Report" << endl;
	}
	~SalesReport() override
	{
		cout << "Sales Report Destructor Called" << endl;
	}
};

class HRReport :public Report
{
public:

	void generateReport() override
	{
		cout << "Generating HR Report" << endl;
	}
	~HRReport() override
	{
		cout << "HR Report Destructor Called" << endl;
	}
};

class TechReport :public Report
{
public:

	void generateReport() override
	{
		cout << "Generating Technical Report" << endl;
	}
	~TechReport() override
	{
		cout << "Tech Report Destructor Called" << endl;
	}
};


int main()
{
	Report* pointer[3];
	pointer[0] = new SalesReport(); 
	pointer[1] = new HRReport(); 
	pointer[2] = new TechReport(); 

	cout << endl;

	for (int i = 0; i < 3; i++)
	{
		pointer[i]->generateReport();
	}

	for (int i = 0; i < 3; i++)
	{
		delete[]pointer[i];
	}
	

	return 0;
}