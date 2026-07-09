#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    const int TABLE_SIZE = 256;
    int last[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++)
        last[i] = -1;

    int l = 0;
    int position = 0;
    int ans = 0;

    for (int r = 0; r < (int)s.size(); r++) {
        unsigned char c = s[r];

        if (last[c] >= l) {
            l = last[c] + 1;
        }

        last[c] = r;
        int len = r - l + 1;

        if (len > ans) {
            ans = len;
            position = l;
        }
    }

    cout << "Position: " << position << "\nLenght: " << ans;
    return 0;
}
