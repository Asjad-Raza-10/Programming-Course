#include <iostream>
using namespace std;

class Developer
{
private:
	string devname;
	string role;
	int skill;
public:
	Developer(string d = "", string r = "", int s = 0)
	{
		devname = d;
		role = r;
		skill = s;
	}

	void setdevname(string d)
	{
		devname = d;
	}

	void setrole(string c)
	{
		role = c;
	}

	void setskill(int h)
	{
		skill = h;
	}

	string getdevname()
	{
		return devname;
	}

	string getrole()
	{
		return role;
	}

	int getskill()
	{
		return skill;
	}

	void DisplayDeveloperInfo()
	{
		cout << "Name: " << devname << endl;
		cout << "Role: " << role << endl;
		cout << "Skill Level: " << skill << endl;
	}
};

class Project
{
private:
	string projname;
	string timeline;
	Developer* devlist[3];
	int devCount;
public:
	Project(string n = "", string l = "")
	{
		projname = n;
		timeline = l;
		devCount = 0;
	}
		
	void setprojname(string h)
	{
		projname = h;
	}

	void setdevCount(int d)
	{
		devCount = d;
	}

	void settimeline(string l)
	{
		timeline = l;
	}

	void setdevlist(Developer* dl)
	{
		*devlist = dl;
	}

	string getprojname()
	{
		return projname;
	}

	string gettimeline()
	{
		return timeline;
	}

	int getdevCount()
	{
		return devCount;
	}

	Developer** getdevlist()
	{
		return devlist;
	}

	void addDeveloper(Developer* dev)
	{
		if (devCount < 3)
		{
			devlist[devCount++] = dev;
		}
	}

	void displayProjectDetails()
	{
		cout << endl;
		cout << "Project Name: " << projname << endl;
		cout << "timeline: " << timeline << endl;

		cout << endl << "Developers Assigned: " << endl << endl;
		for (int i = 0; i < devCount && (devlist + i != nullptr); i++)
		{
			devlist[i]->DisplayDeveloperInfo();
			cout << endl << "---------------------------------------------------------------------------------------" << endl;
		}
	}

};




int main()
{
	Developer D1("Alice", "Frontend", 7);
	Developer D2("Bob", "Backend", 8);
	Developer D3("Charlie", "Frontend", 6);

	Project P1("AI Chatbot", "4 Months");
	P1.addDeveloper(&D1);
	P1.addDeveloper(&D2);
	P1.displayProjectDetails();

	Project P2("E Commerce Platform", "6 Months");
	P2.addDeveloper(&D2);
	P2.addDeveloper(&D3);
	P2.displayProjectDetails();

	return 0;
}
