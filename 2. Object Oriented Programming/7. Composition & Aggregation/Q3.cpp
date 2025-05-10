#include <iostream>
using namespace std;

class Doctor
{
private:
	string docname;
	string phone;
	string specialization;
public:
	Doctor(string d = "", string s = "", string p = "")
	{
		docname = d;
		phone = p;
		specialization = s;
	}

	void setdocname(string d)
	{
		docname = d;
	}

	void setphone(string c)
	{
		phone = c;
	}

	void setspecialization(string h)
	{
		specialization = h;
	}

	string getDocName()
	{
		return docname;
	}

	string getphone()
	{
		return phone;
	}

	string getSpecialization()
	{
		return specialization;
	}

};

class Hospital
{
private:
	string hospname;
	string location;
	Doctor* doclist;
	int docCount;
public:
	Hospital(string n = "", string l = "", int c = 0, Doctor* d = nullptr) :doclist(d)
	{
		hospname = n;
		location = l;
		docCount = c;
	}

	void sethospname(string h)
	{
		hospname = h;
	}

	void setdocCount(int d)
	{
		docCount = d;
	}

	void setlocation(string l)
	{
		location = l;
	}

	void setDocList(Doctor* dl)
	{
		doclist = dl;
	}

	string getHospName()
	{
		return hospname;
	}

	string getLocation()
	{
		return location;
	}

	int getdocCount()
	{
		return docCount;
	}

	Doctor* getDocList()
	{
		return doclist;
	}


	void display()
	{
		cout << endl;
		cout << "Hospital Name: " << hospname << endl;
		cout << "Location: " << location << endl;
		cout << endl << "Associated Doctors: " << endl << endl;
		for (int i = 0; i < docCount && (doclist + i != nullptr); i++)
		{
			cout << "Doctor Name: " << doclist[i].getDocName() << endl;
			cout << "Specialization: " << doclist[i].getSpecialization() << endl;
			cout << "Contact: " << doclist[i].getphone() << endl;
			cout << "---------------------------------------------------------------------------------------" << endl;
		}	
	}

};




int main()
{
	Doctor* D1 = new Doctor[2];
	D1[0] = Doctor("Dr. Alice", "Cardiologist", "123-456-7890");
	D1[1] = Doctor("Dr. Bob", "Neurologist", "987-654-3210");

	Hospital H1("City Hospital", "Downtown", 2, D1);
	cout << endl << "===== Hostpital 1 =====" << endl;
	H1.display();

	Doctor* D2 = new Doctor[2];
	D2[0] = Doctor("Dr. Bob", "Neurologist", "987-654-3210");
	D2[1] = Doctor("Dr. Carol", "Dermatologist", "555-123-4567");

	Hospital H2("Metro Hospital", "Uptown", 2, D2);
	cout << endl << "===== Hostpital 2 =====" << endl;
	H2.display();

	delete[]D1;
	delete[]D2;

	return 0;
}
