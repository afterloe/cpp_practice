#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    string str1 = "afterloe";
    cout << str1 << endl;
    cout << str1.size() << endl;
    char *p = (char *)malloc(sizeof(char[128]));
    strcpy(p, "hello");
    printf("%s\n", p);
    printf("%d\n", strlen(p));
    system("pause");
    free(p);
    return 0;
}