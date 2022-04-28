#include <iostream>

#include "Person.pb.cc"

using namespace std;

int main()
{
    Person p;
    p.set_name("afterloe");
    p.set_sex(Male);
    p.set_id(1101);

    cout << p.name() << " | " << p.sex() << " | " << p.id() << endl;

    return 0;
}