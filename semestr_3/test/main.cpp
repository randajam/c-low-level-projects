#include <iostream>
#include <fstream>
#include "vector.cpp"

using namespace std;

int main() {
    ifstream in1("in1.txt");
    ifstream in2("in2.txt");
    if (in1.is_open() && in2.is_open()) {
        int kol1, kol2, d;
        cin >> d;
        in1 >> kol1;
        in2 >> kol2;
        Set_Vectors<int> s1(d, kol1), s2(d, kol2);

        in1 >> s1;
        in2 >> s2;

        cout << "Vector 1:\n" << s1 << "\n";
        cout << "Vector 2:\n" << s2 << "\n";

        s1 += s2;

        cout << "Vector 1+2:\n" << s1;
    }

    return 0;
}