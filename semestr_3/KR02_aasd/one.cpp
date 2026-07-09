#include <iostream>

using namespace std;

int main() {
    char mass[100];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> mass[i];
    }
    int l = 0, r = n - 1;
    bool is_palind = true;
    while ((l != r) && (l + 1 != r)) {
        if (mass[l] != mass[r]) {
            is_palind = false;
        }
        l++, r--;
    }
    cout << is_palind;

    return 0;
}