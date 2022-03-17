#include "iostream"
#include "ctime"

using namespace std;

void fillArray(int*, int);
int findMax(int*, int);

int main(void) {
    srand((unsigned)time(NULL));
    int target[10];
    fillArray(target, 10);
    int max = findMax(target, 10);
    cout << "max value is " << max << endl;
} 

void fillArray(int *p, int size) {
    for (int i = 0; i < size; i++) {
        *(p + i) = rand();
    }
    for (int i = 0; i < size; i++) {
        cout << "" << *(p + i) << ", ";
    }
    cout << endl;
}

int findMax(int *p, int size) {
    int max = *p;
    for (int i = 0; i < size; i++) {
        if (*(p + i) > max) {
            max = *(p + i);
        }
    }
    return max;
}
