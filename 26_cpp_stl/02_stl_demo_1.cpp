#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>

#include <ctime>

using namespace std;

class Student
{
public:
    string name;
    int score;
};

void initStudent(vector<Student> &stuList, int size = 5)
{
    string stuName = "ABCDEFG";
    for (int i = 0; i < size; i++)
    {
        Student stu;
        char buf[64];
        sprintf(buf, "学生%c", stuName.at(i));
        stu.name = string(buf);
        stu.score = 0;
        stuList.push_back(stu);
    }
}

void randomScore(deque<int> &sources, int num = 10)
{
    for (int i = 0; i < num; i++)
    {
        int source = rand() % 70 + 30;
        sources.push_back(source);
    }
    sort(sources.begin(), sources.end());
    sources.pop_front();
    sources.pop_back();
}

void doScore(vector<Student> &stuList)
{
    for (vector<Student>::iterator current = stuList.begin(); current < stuList.end(); current++)
    {
        deque<int> sources;
        randomScore(sources);
        int total = 0;
        for (deque<int>::iterator it = sources.begin(); it < sources.end(); it++)
        {
            total += *it;
        }
        int source = total / sources.size();
        current->score = source;
    }
}

void printfStuSource(vector<Student> &stuList)
{
    sort(stuList.begin(), stuList.end(), [](Student a, Student b)
         { return a.score > b.score; });
    int rank = 1;
    for (vector<Student>::iterator it = stuList.begin(); it < stuList.end(); it++)
    {
        cout << "No. " << rank << "\t";
        cout << "Name: " << it->name << " Source: " << it->score << endl;
        rank++;
    }
}

int main()
{
    srand(time(NULL));
    vector<Student> stuList;
    initStudent(stuList);
    doScore(stuList);
    printfStuSource(stuList);
    return EXIT_SUCCESS;
}