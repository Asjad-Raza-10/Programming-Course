#include <iostream>
using namespace std;

class CPU 
{
private:
	int cores;
	float speed;
public:
	CPU(int c = 0, float s = 0.0)
	{
		cores = c;
		speed = s;
	}

	void setCores(int c)
	{
		cores = c;
	}

	void setSpeed(float s)
	{
		speed = s;
	}
	
	int getCores()
	{
		return cores;
	}

	float getSpeed()
	{
		return speed;
	}

};

class Computer
{
private:
	CPU cpu;
	string name;
	int size;
public:
	Computer(int c = 0, float s = 0.0, string n = "", int sz = 0) :cpu(c, s)
	{
		name = n;
		size = sz;
	}

	void configureCPU(int c, float s)
	{
		cpu.setCores(c);
		cpu.setSpeed(s);
	}

	void display()
	{
		cout << endl << "Computer Details:" << endl;
		cout << "Computer Brand: " << name << endl;
		cout << "RAM Size: " << size << " GB" << endl;
		cout << "CPU Cores: " << cpu.getCores() << endl;
		cout << "CPU Speed: " << cpu.getSpeed() << " GHz" << endl;
	}

};




int main()
{
	Computer C1(12, 4.0, "Dell", 16);
	C1.display();
	
	cout << endl << "Configuring CPU Details:" << endl;

	C1.configureCPU(8, 3.5);
	C1.display();

	return 0;
}