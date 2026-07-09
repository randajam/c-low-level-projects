#include <iostream>
#include <fstream>

using namespace std;

#define INFI_PATH "input.txt"
#define OUTFI_PATH "output.txt"

int main() {
    ifstream in(INFI_PATH);
    ofstream out(OUTFI_PATH);

    if (!in.is_open() || !out.is_open()) {
        return 1;
    }

    int n;
    int bits[32]{0};
    long res = 0;

    if (in >> n) {
        for (int i = 0; i < n; i++) {
            long num;
            in >> num;
            for (int j = 0; j < 32; j++) {
                if (num & (1 << j)) {
                    bits[j]++;
                }
            }
        }
    }

    for (int i = 0; i < 32; i++) {
        if (bits[i] >= 3 || bits[i] == 0) {
            bits[i] %= 3;
        } else {
            bits[i] = 1;
        }
    }

    for (int i = 31; i >= 0; i--) {
        res += bits[i] * (1 << i);
    }

    out << res << endl;
    cout << "Result: " << res << endl;


    in.close();
    out.close();
    
    return 0;
}