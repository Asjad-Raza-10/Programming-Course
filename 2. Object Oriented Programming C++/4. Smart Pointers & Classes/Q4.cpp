#include<iostream>
using namespace std;

class Book 
{
private:
	string title;
	string author;
	int ISBN;
public:
	Book()
	{
		title = "Unknown";
		author = "Unknown";
		ISBN = 0;
	}
	
	Book(string t, string a, int i)
	{
		title = t;
		author = a;
		ISBN = i;

	}
	
	void setTitle(string a)
	{
		title = a;
	}
	
	void setAuthor(string b)
	{
		author = b;
	}
	
	void setISBN(int c)
	{
		ISBN = c;
	}
	
	string getTitle()
	{
		cout << "Title is: " << title << endl;
		return title;
	}
	
	string getAuthor()
	{
		cout << "Author is: " << author << endl;
		return author;
	}
	
	int getISBN()
	{
		cout << "ISBN is: " << ISBN << endl;
		return ISBN;
	}
	
	void Bookdetails()
	{
		cout << "Book Details:" << endl;
		cout << "Title is: " << title << endl;;
		cout << "Author is: " << author << endl;
		cout << "ISBN is: " << ISBN << endl;
	}
};

int main()
{
	
	Book B1;
	B1.Bookdetails();
	Book B2;
	B2.setTitle("Book 2");
	B2.setAuthor("Raza");
	B2.setISBN(700);

	B2.Bookdetails();

	return 0;

}