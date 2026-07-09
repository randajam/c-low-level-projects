#include <iostream>
#include <cstdlib>

#include "queue.h"

using namespace std;

int main() {
    cout << "=== TEST 1: Insert + get_min + extract_min ===\n";

    Priority_Queue<int> pq;
    pq.insert(5);
    pq.insert(3);
    pq.insert(10);
    pq.insert(1);

    cout << "Min = " << pq.get_min() << " (expected 1)\n";
    cout << "Extracted: ";
    cout << pq.extract_min() << " ";
    cout << pq.extract_min() << " ";
    cout << pq.extract_min() << " ";
    cout << pq.extract_min() << " ";
    cout << "\n";


    cout << "\n=== TEST 2: Build from array (O(n)) ===\n";

    int arr[] = {9, 4, 7, 1, -3, 2};
    Priority_Queue<int> pq2(arr, 6);

    cout << "Extracting in sorted order: ";
    while (true) {
        try {
            cout << pq2.extract_min() << " ";
        } catch (...) { break; }
    }
    cout << "\n(expected: -3 1 2 4 7 9)\n";


    cout << "\n=== TEST 3: Copy constructor ===\n";

    Priority_Queue<int> a;
    a.insert(8);
    a.insert(2);
    a.insert(11);

    Priority_Queue<int> b = a;

    cout << "Original min = " << a.get_min() << "\n";
    cout << "Copy min     = " << b.get_min() << "\n";

    cout << "Extracting from copy: ";
    while (true) {
        try {
            cout << b.extract_min() << " ";
        } catch (...) { break; }
    }
    cout << "\n";


    cout << "\n=== TEST 4: Random stress-test ===\n";

    Priority_Queue<int> big;
    const int N = 10000;

    for (int i = 0; i < N; i++)
        big.insert(rand() % 100000);

    bool ok = true;
    int prev = big.extract_min();
    for (int i = 1; i < N; i++) {
        int x = big.extract_min();
        if (x < prev) ok = false;
        prev = x;
    }

    cout << "Heap property preserved? " << (ok ? "YES" : "NO") << "\n";

    return 0;
}