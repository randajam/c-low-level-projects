#include <iostream>
#include <cstdlib>
#include <ctime>

#include "function.h"

using namespace std;

template <typename T>
bool is_sorted(const T* mas, int size) {
    for (int i = 1; i < size; i++)
        if (mas[i-1] > mas[i])
            return false;
    return true;
}

void print_test(const string& name, bool ok) {
    cout << "[ " << (ok ? "OK" : "FAIL") << " ] " << name << endl;
}


int main() {
    srand(time(0));

    // TEST 1 — empty
    {
        int* a = nullptr;
        quick_sort(a, 0);
        print_test("Empty array", true);
    }

    // TEST 2 — single element
    {
        int a[1] = {42};
        quick_sort(a, 1);
        print_test("Single element", a[0] == 42);
    }

    // TEST 3 — all equal
    {
        int a[10];
        for (int i = 0; i < 10; i++) a[i] = 7;

        quick_sort(a, 10);
        print_test("All equal", is_sorted(a, 10));
    }

    // TEST 4 — sorted already
    {
        int a[10];
        for (int i = 0; i < 10; i++) a[i] = i;

        quick_sort(a, 10);
        print_test("Already sorted", is_sorted(a, 10));
    }

    // TEST 5 — reverse order
    {
        int a[10];
        for (int i = 0; i < 10; i++) a[i] = 10 - i;

        quick_sort(a, 10);
        print_test("Reverse order", is_sorted(a, 10));
    }

    // TEST 6 — random
    {
        const int N = 5000;
        int a[N];
        for (int i = 0; i < N; i++) a[i] = rand() % 1000;

        quick_sort(a, N);
        print_test("Random data", is_sorted(a, N));
    }

    return 0;
}
