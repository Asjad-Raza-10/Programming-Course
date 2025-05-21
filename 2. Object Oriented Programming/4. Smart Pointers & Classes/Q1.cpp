#include <iostream>
#include <memory>
using namespace std;

class Student
{
  public:
    int Roll_No;
    string Name;
    string Program;

    Student()
    {
        Roll_No = 0;
        Name = "Unknown";
        Program = "Unknown";
        cout << "A record for student(" << Name << ", " << Roll_No << ", " << Program << ") was created." << endl;
    }

    Student(const int &Roll_no, const string &name, string program)
    {
        Roll_No = Roll_no;
        Name = name;
        Program = program;
        cout << "A record for student(" << Name << ", " << Roll_No << ", " << Program << ") was created." << endl;
    }

    unique_ptr<Student> createStudent()
    {
        unique_ptr<Student> object_ptr = make_unique<Student>(Roll_No, Name, Program);
        return object_ptr;
    }

    void display()
    {
        cout << "Name: " << Name << endl;
        cout << "Roll No: " << Roll_No << endl;
        cout << "Program: " << Program << endl;
    }
};

int main()
{
    Student s1(583, "Asjad", "BSCS");
    cout << endl << "Student Details : " << endl;
    s1.display();

    unique_ptr<Student> s2 = s1.createStudent();
    unique_ptr<Student> s3 = move(s2);

    cout << endl << "After Ownership Transfer : " << endl << "Student Details:" << endl;
    (*s3).display();

    return 0;
}