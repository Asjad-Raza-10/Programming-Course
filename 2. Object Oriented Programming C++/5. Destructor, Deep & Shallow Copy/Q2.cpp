#include <iostream>
#include <string.h>

using namespace std;

class Cart {

private:
	int size;
	string* products;

public:
	Cart(string p[] = nullptr, int s = 0)
	{
		size = s;
		products = new string[size];
		for (int i = 0; i < size; i++)
		{
			products[i] = p[i];
		}
	}

	void display()
	{
		cout << "Shopping Cart Contains:";
		for (int i = 0; i < size; i++)
		{
			cout << products[i] << ", ";
		}
		cout << endl;
	}

	//deep copy using copy construct
	Cart(Cart& RHS)
	{
		size = RHS.size;
		products = new string[size];
		for (int i = 0; i < size; i++)
		{
			products[i] = RHS.products[i];
		}
		
	}

	//move constructor
	Cart(Cart&& RHS)
	{
		size = RHS.size;
		products = RHS.products;
		RHS.products = nullptr;
		RHS.size = 0;
	}

	//destructor
	~Cart()
	{
		if (products != nullptr)
		{
			delete[]products;
			products = nullptr;
		}
	}

};

int main()
{
	cout << "Customer A's Cart" << endl;
	
	const int size_1 = 3;
	string P1[size_1] = { "Laptop","Headphones","Mouse" };

	Cart C1(P1, size_1);

	C1.display();
	cout << endl;

	cout << "Cutomer B duplicates the cart (Deep Copy Constructor Called):" << endl;
	Cart C2 = C1;

	C2.display();
	cout << endl;

	cout << "Transferring Cart from Customer B to Customer C (Move Constructor Called):" << endl;
	Cart C3 = move(C2);

	C3.display();
	
	cout << endl << "Customer B's cart is removed:" << endl;
	C2.display();

	return 0;
}
