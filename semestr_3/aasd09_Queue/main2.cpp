#include <iostream>
#include <vector>
#include <cassert>

#include "queue.h"

using namespace std;

bool is_sorted(const vector<int>& v) {
    for (int i = 0; i + 1 < v.size(); i++)
        if (v[i] > v[i + 1])
            return false;
    return true;
}

void test_case(const vector<int>& input, const string& name) {
    vector<int> a = input;
    heap_sort(a.data(), a.size());
    bool ok = is_sorted(a);

    cout << "[ " << (ok ? "OK" : "FAIL") << " ] " << name << endl;

    if (!ok) {
        cout << "Input: ";
        for (int x : input) cout << x << " ";
        cout << "\nOutput: ";
        for (int x : a) cout << x << " ";
        cout << endl;
    }

    assert(ok);
}

int main() {
    // 1. Empty
    test_case({}, "Empty array");

    // 2. Single
    test_case({5}, "Single element");

    // 3. All equal
    test_case({7,7,7,7,7}, "All equal");

    // 4. Already sorted
    test_case({1,2,3,4,5,6,7}, "Already sorted");

    // 5. Reverse sorted
    test_case({9,8,7,6,5,4,3,2,1}, "Reverse sorted");

    // 6. Random
    test_case({10,3,5,2,8,9,1,4,7,6}, "Random");

    cout << "All tests passed!" << endl;
    return 0;
}