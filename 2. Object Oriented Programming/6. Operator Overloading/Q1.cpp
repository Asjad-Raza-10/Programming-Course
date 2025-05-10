#include <iostream>
using namespace std;

class fraction {

private:
	int num;
	int denum;
	
public:
	fraction(int n = 0, int d = 1)
	{
		num = n;
		denum = d;
	}

	fraction(fraction &RHS)
	{
		num = RHS.num;
		denum = RHS.denum;
	}

	fraction(fraction&& RHS)
	{
		num = RHS.num;
		denum = RHS.denum;
		RHS.num = 1;
		RHS.denum = 1;
	}

	void display()
	{
		cout << num << "/" << denum << endl;
	}

	fraction operator = (fraction RHS)
	{
		num = RHS.num;
		denum = RHS.denum;
	}

	int GCD(int x, int y)
	{
		if (y > x)
		{
			int temp = y;
			y = x;
			x = temp;
		}
		if ((x % y) == 0)
		{
			return y;
		}
		return GCD(y, x % y);
	}

	void simplify()
	{
		int h = GCD(num, denum);
		num /= h;
		denum /= h;
	}

	fraction operator + (fraction f)
	{
		int n = num * f.denum + denum * f.num;
		int d = denum * f.denum;
		fraction r(n, d);
		r.simplify();
		cout << "Sum: "; r.display(); cout << endl;
		return r;
	}

	fraction operator - (fraction f)
	{
		int n = num * f.denum - denum * f.num;
		int d = denum * f.denum;
		fraction r(n, d);
		r.simplify();
		cout << "Difference: "; r.display(); cout << endl;
		return r;
	}

	fraction operator * (fraction f)
	{
		int n = num * f.num;
		int d = denum * f.denum;
		fraction r(n, d);
		r.simplify();
		cout << "Product: "; r.display(); cout << endl;
		return r;
	}
	
	fraction operator / (fraction f)
	{
		int n = num * f.denum;
		int d = denum * f.num;
		fraction r(n, d);
		r.simplify();
		cout << "Division: "; r.display(); cout << endl;
		return r;
	}

	bool operator == (fraction f)
	{
		f.simplify();
		(*this).simplify();
		if (num == f.num && denum == f.denum)
		{
			return true;
		}
		return false;
	}


};


int main()
{

	cout << endl << "Fraction 1: ";
	fraction f1(2, 3);
	f1.display();
	
	cout << "Fraction 2: ";
	fraction f2(3, 4);
	f2.display();

	cout << endl;

	fraction sum = f1 + f2;
	fraction difference = f1 - f2;
	fraction product = f1 * f2;
	fraction division = f1 / f2;

	cout << "Are fractions equal? ";
	if (f1 == f2)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

	cout << endl << "Is Fraction 1 equal to 4/6? ";
	
	fraction f3(4 , 6);

	if (f1 == f3)
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}

	cout << endl;

	return 0;
}