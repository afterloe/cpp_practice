#include <iostream>

using namespace std;

int add(int, int);

int main() {
    int a, b;
    a = 12;
    b = 13;
    cout<<"sum is "<< add(a, b) << endl;
    return 0;
}

int add(int a, int b) {
    return a + b;
}