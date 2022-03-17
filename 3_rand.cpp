#include <iostream>
#include <ctime>

using namespace std;

// 使用随机数
int main(void) {
    srand((unsigned)time(NULL));
    for (int i = 0; i< 10; i++) {
        cout << rand() << endl;
    }
}