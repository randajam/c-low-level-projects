#include "functions.h"
#include <iostream>

using namespace std;

int main() {
    FindDel(23435, 1);
    int a[10] = {10, 9, 8, 7, 6 , 2, 3, 11, 4, 2};
    cout << endl;
    BubbleSort(a);
    for (int i = 0; i < 10; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << BinSearch(a, 4, 0, 9) << endl;
    return 0;
}