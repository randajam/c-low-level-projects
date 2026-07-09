#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

#include "function.h"

using namespace std;

template <class T>
bool is_sorted_asc(const vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++)
        if (v[i - 1] > v[i]) return false;
    return true;
}

template <class T>
bool test_case(const vector<T>& src) {
    vector<T> a = src;
    vector<T> b = src;

    if (!a.empty())
        merge_sort(&a[0], a.size());

    sort(b.begin(), b.end());

    return a == b;
}

void print_result(const string& name, bool ok) {
    cout << (ok ? "[ OK ] " : "[FAIL] ") << name << endl;
}


int main() {
    srand((unsigned)time(nullptr));

    {
        vector<int> v;
        bool ok = test_case(v);
        print_result("Empty array", ok);
    }

    {
        vector<int> v = {42};
        bool ok = test_case(v);
        print_result("Single element", ok);
    }

    {
        vector<int> v = {5,5,5,5,5,5};
        bool ok = test_case(v);
        print_result("All equal", ok);
    }

    {
        vector<int> v = {9, 1, 8, 2, 7, 3, 6, 4, 5};
        bool ok = test_case(v);
        print_result("Known numbers", ok);
    }

    {
        vector<int> v(1000);
        for (int& x : v) x = rand() % 10000;

        bool ok = test_case(v);
        print_result("Random integers (1000)", ok);
    }

    {
        vector<double> v(500);
        for (double &x : v) x = (rand() % 10000) / 10.0;

        bool ok = test_case(v);
        print_result("Random doubles", ok);
    }

    {
        vector<string> v = {
            "orange", "apple", "pear", "banana", "kiwi", "grape"
        };

        bool ok = test_case(v);
        print_result("Strings", ok);
    }

    cout << "\n=== ALL TESTS COMPLETED ===\n";
}
