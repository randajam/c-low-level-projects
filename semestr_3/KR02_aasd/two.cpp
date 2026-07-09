#include <iostream>
#include <string>

using namespace std;

void funct(int n, int k, string res) {
    if (n < k && k > 0) {
        return;
    }
    if (n == 0 && k == 0) {
        cout << res << endl;
    }
    if (n > 0 && k > 0) {
        funct(n-1, k, res + "0");
        funct(n-1, k-1, res + "1");
    }
    if (n > 0 && k == 0) {
        funct(n - 1, k, res + "0");
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    funct(n, k, "");
    return 0;
}