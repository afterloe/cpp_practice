#include <iostream>
#include <string>

using namespace std;

struct Student
{
    string mName;
    int mAge;

    void setName(string name) { mName = name; }
    void setAge(int age) { mAge = age; }
    void showInfo() { cout << "name: " << mName << " Age: " << mAge << endl; }
};

int main()
{
    Student stu;
    stu.setName("joe");
    stu.setAge(10);
    stu.showInfo();

    return EXIT_SUCCESS;
}