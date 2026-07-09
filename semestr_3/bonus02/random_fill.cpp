#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define OUTFI_PATH "input.txt"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int n = 300001;
    long min = 0, max = 2e9;

    ofstream out(OUTFI_PATH);
    if (out.is_open()) {
        out << n << endl;
        for (int i = 0; i < n; i++) {
            out << rand() % (max - min + 1) + min << endl;
        }
    }

    return 0;
}