#include "functions.h"
#include <iostream>

using namespace std;

int main() {
    int n{10}, x{2}, m{7};
    cout << "Sum 10: " << sum(n) << endl;
    cout << "isSquare 2: " << isSquare(2*2*2,x) << endl;
    cout << "C_10_7: " << C(n, m) << endl;
    cout << "2**-10: " << pow(x, -n) << endl;
    return 0;
}