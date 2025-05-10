#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Product 
{
public:
	string Name;
	float Price;
	
	Product()
	{
		Name = "Unknown";
		Price = 0.0;
	}

	Product(string n, int p) 
	{
		Name = n;
		Price = p;
		cout << "Product \"" << Name << "\" Created" << endl;
	}
	
	void display() {
		cout << "Name: " << Name << endl;
		cout << "Price: " << Price << endl;
	}

};

int main() 
{
	shared_ptr<Product> Mobile_1 = make_shared<Product>("Mobile", 20000);
	shared_ptr<Product> Mobile_2 = Mobile_1;
	
	cout << "Users pointing at Product (Mobile): " << Mobile_1.use_count() << endl;
	
	shared_ptr<Product> Mobile_3 = Mobile_1;
	
	(*Mobile_1).display();

	cout << "Users pointing at Product (Mobile): " << Mobile_1.use_count() << endl;

	Mobile_3.reset();
	Mobile_2.reset();
	Mobile_1.reset();

	cout << "Users pointing at Product (Mobile): " << Mobile_1.use_count() << endl;

	shared_ptr<Product> Laptop_1 = make_shared<Product>("Laptop", 150000);

	cout << "Users pointing at Product (Laptop): " << Laptop_1.use_count() << endl;
	
	(*Laptop_1).display();
	
	shared_ptr<Product> Laptop_2 = Laptop_1;
	shared_ptr<Product> Laptop_3 = Laptop_1;
	shared_ptr<Product> Laptop_4 = Laptop_1;
	
	cout << "Users pointing at Product (Laptop): " << Laptop_3.use_count() << endl;
	
	return 0;
}