#include <iostream>

#include "queue.h"

using namespace std;

int main() {
    int A[] = {7, 2, 5, 1, 9, 3};
    int n = 6;

    cout << "Array: ";
    for (int x : A) cout << x << " ";
    cout << "\n";

    for (int k = 1; k <= n; k++) {
        cout << k << "-й минимальный элемент = "
             << kth_min(A, n, k) << "\n";
    }

    return 0;
}