#include <iostream>
#include <string>

using namespace std;

class Student
{
    public:
        string name;
        int age;
};

ostream &operator<<(ostream &out, Student &stu)
{
    out << stu.name << " | " << stu.age;
    return out;
}

int main()
{
    Student stu;
    stu.name = "joe";
    stu.age = 10;
    cout << stu << endl;
    return EXIT_SUCCESS;
}