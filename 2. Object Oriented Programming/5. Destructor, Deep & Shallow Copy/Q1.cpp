#include <iostream>
#include <string.h>

using namespace std;

class Rectangle
{

  private:
    int width;
    int height;
    char *color;

  public:
    Rectangle(char c[] = nullptr, int w = 0, int h = 0)
    {
        width = w;
        height = h;
        int size = strlen(c);
        color = new char[size];
        strcpy(color, c);
    }

    void setColor(char c[])
    {
        if (color != nullptr)
        {
            delete[] color;
        }
        int size = strlen(c);
        color = new char[size];
        strcpy(color, c);

        cout << "New color of Rectangle is: " << color << endl;
    }

    void display()
    {
        cout << "Rectangle: Color = " << color << ", Width = " << width << ", Height = " << height << endl;
    }

    // deep copy using copy constructor
    Rectangle(Rectangle &RHS)
    {
        width = RHS.width;
        height = RHS.height;
        int size = strlen(RHS.color);
        color = new char[size];
        strcpy(color, RHS.color);
    }

    // move constructor
    Rectangle(Rectangle &&RHS)
    {
        width = RHS.width;
        height = RHS.height;
        color = RHS.color;
        RHS.color = nullptr;
        RHS.height = 0;
        RHS.width = 0;
    }

    // destructor
    ~Rectangle()
    {
        if (color != nullptr)
        {
            delete[] color;
            color = nullptr;
        }
    }
};

int main()
{
    cout << "Creating Original Rectangle" << endl;
    Rectangle R1("Red", 10, 20);

    R1.display();

    cout << endl << "Copying Rectangle (Deep Copy Constructor Called):" << endl;
    Rectangle R2 = R1;

    R2.display();

    cout << endl << "Modifying Color of Copy:" << endl;
    R2.setColor("Blue");
    R2.display();
    R1.display();

    cout << endl << "Using Move Constructor:" << endl;
    Rectangle R3 = move(R2);

    R3.display();

    cout << endl << "Rectangle 2's record is removed now:" << endl;
    R2.display();

    return 0;
}
