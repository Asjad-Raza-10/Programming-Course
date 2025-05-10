#include <iostream>
using namespace std;

class Distance {

private:
	int* feet;
	int* inches;

public:
	Distance()
	{
		feet = nullptr;
		inches = nullptr;
	}

	Distance(int f, int i)
	{
		feet = new int(f);
		inches = new int(i);
	}

	Distance(Distance& RHS)
	{
		feet = new int (*RHS.feet);
		inches = new int (*RHS.inches);
	}

	Distance(Distance&& RHS)
	{
		feet = RHS.feet;
		inches = RHS.inches;
		RHS.feet = nullptr;
		RHS.inches = nullptr;
	}

	void display()
	{
		cout << *feet << " feet " << *inches << " inches" << endl;
	}

	void operator = (const Distance &RHS)
	{
		feet = new int(*RHS.feet);
		inches = new int(*RHS.inches);
	}

	void operator = (Distance&& RHS)
	{
		feet = new int(*RHS.feet);
		inches = new int(*RHS.inches);
		RHS.feet = nullptr;
		RHS.inches = nullptr;
	}

	void simplify()
	{
		while (*inches >= 12)
		{
			(*feet)++;
			(*inches) -= 12;
		}
	}

	Distance operator + (Distance f)
	{
		int ft = (*feet) + (*f.feet);
		int in = (*inches) + (*f.inches);
		Distance r(ft, in);
		r.simplify();
		cout << "Sum: "; r.display(); cout << endl;
		return r;
	}

	bool operator == (Distance f)
	{
		f.simplify();
		(*this).simplify();
		if ((((*feet)*12) + (*inches)) == (((*f.feet) * 12) + (*f.inches)))
		{
			return true;
		}
		return false;
	}

	bool operator < (Distance f)
	{
		f.simplify();
		(*this).simplify();
		if ((((*feet) * 12) + (*inches)) < (((*f.feet) * 12) + (*f.inches)))
		{
			return true;
		}
		return false;
	}

	~Distance()
	{
		if (feet != nullptr)
		{
			feet = nullptr;
		}
		if (inches != nullptr)
		{
			inches = nullptr;
		}
	}
};


int main()
{

	cout << endl << "Distance 1: ";
	Distance d1(5, 10);
	d1.display();

	cout << "Distance 2: ";
	Distance d2(3, 11);
	d2.display();

	cout << endl;

	Distance sum = d1 + d2;
		

	cout << "Are d1 and d2 equal? ";
	if (d1 == d2)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

	cout << endl << "Is d1 less than d2? ";
	if (d1 < d2)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

	cout << endl << "Copied Distance (d4 from d1): ";
	Distance d4 = d1;
	d4.display();

	cout << endl;

	return 0;
}