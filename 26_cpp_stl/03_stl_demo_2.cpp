#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <string>

#include <ctime>

using namespace std;

class Person
{
public:
    string name;
};

void enter(list<Person> &elevator, int floor)
{
    if (14 == floor)
    {
        return;
    }
}

void getOut(list<Person> &elevator, int floor)
{
    if (0 == floor)
    {
        return;
    }
}

void printfElevatorInfo(list<Person> &elevator);

void run(list<Person> &elevator, int floor=15)
{
    for(int i = 0; i < floor; i++)
    {
        enter(elevator, i);
        getOut(elevator, i);
        printfElevatorInfo(elevator);
    }
}

int main()
{
    list<Person> elevator;
    run(elevator);
    return EXIT_SUCCESS;
}