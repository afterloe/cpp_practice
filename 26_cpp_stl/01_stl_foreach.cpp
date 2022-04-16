#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Person
{
public:
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }

public:
    string name;
    int age;
};

// 运算符重载
ostream &operator<<(ostream &out, Person &p)
{
    out << "Name: " << p.name << " Age: " << p.age << endl;
    return out;
}

void print_person(Person &p)
{
    cout << p.name << " | " << p.age << endl;
}

void test_foreach()
{
    vector<Person> list;
    list.push_back(Person("afterloe", 10));
    list.push_back(Person("grace", 8));
    list.push_back(Person("jor", 11));
    list.push_back(Person("blu", 7));
    list.push_back(Person("hu", 6));

    vector<Person>::iterator begin = list.begin();
    vector<Person>::iterator end = list.end();

    // 回调函数
    // for_each(begin, end, print_person);

    // lambda
    for_each(begin, end, [](Person &p)
             { cout << p.name << " - " << p.age << endl; });
}

void test_iterator()
{
    vector<Person> list;
    list.push_back(Person("afterloe", 10));
    list.push_back(Person("grace", 8));
    list.push_back(Person("jor", 11));
    list.push_back(Person("blu", 7));
    list.push_back(Person("hu", 6));

    vector<Person>::iterator begin = list.begin();
    vector<Person>::iterator end = list.end();

    while (begin != end)
    {
        cout << *begin << endl;
        begin++;
    }
}

int main()
{
    test_foreach();
    return EXIT_SUCCESS;
}