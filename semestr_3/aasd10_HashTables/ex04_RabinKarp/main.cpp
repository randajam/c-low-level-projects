#include <iostream>
#include <string>

using namespace std;

const long long B = 256;
const long long M = 1000000007;

long long rabinKarp(const string& text, const string& pattern) {
    int n = text.size();
    int k = pattern.size();
    
    if (k > n) return -1;
    
    long long hash_p = 0;
    long long hash_t = 0;
    
    for (int i = 0; i < k; i++) {
        hash_p = (hash_p * B + pattern[i]) % M;
        hash_t = (hash_t * B + text[i]) % M;
    }
    
    long long power = 1;

    for (int i = 0; i < k - 1; i++)
        power = (power * B) % M;
    
    for (int i = 0; i <= n - k; i++) {
        if (hash_t == hash_p) {
            if (text.substr(i, k) == pattern)
                return i;
        }


        if (i < n - k) {
            hash_t = (hash_t - text[i] * power % M) % M;
            hash_t = (hash_t * B + text[i + k]) % M;
        }
    }

    return -1;
}

int main() {
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text);
    cout << "Введите образец: ";
    getline(cin, pattern);

    long long pos = rabinKarp(text, pattern);

    if (pos == -1)
        cout << "Строка не входит в текст\n";
    else
        cout << "Первое вхождение начинается с позиции: " << pos << endl;

    return 0;
}
