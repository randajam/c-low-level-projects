#include <iostream>

#include "queue.h"

using namespace std;

int main() {
    cout << "=== TEST 1: SUMM ===\n";

    Priority_Queue<double> pq;
    int n = 100000;
    for (double i = 1; i < n; i++) {
        pq.insert(1.0 / i);
    }

    while (pq.get_size() > 1) {
        double a = pq.extract_min();
        double b = pq.extract_min();
        pq.insert(a + b);
    }

    cout << "SUMM = " << pq.get_min() << "\n";
    return 0;
}