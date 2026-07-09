#include "comp.h"
#include "vector.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Vector
    cout << "Введите размеры массивов: ";
    int a_size, b_size;
    cin >> a_size >> b_size;

    Vector<double> a(a_size), b(b_size);

    cout << "Введите массив a: " << endl;
    cin >> a;

    cout << "Введите массив b: " << endl;
    cin >> b;

    Vector<double> c = (a + b) * a;
    cout << "Массив (a + b) * a:\n" << c << endl;
    
    // Complex
    cout << "Введите размеры массивов: ";
    int A_size, B_size;
    cin >> A_size >> B_size;

    Vector<Comp> A(A_size), B(B_size);
    
    ifstream fin("input.txt");

    if (fin.is_open()) {
        fin >> A;
        fin >> B;
    }
    fin.close();
    
    cout << "Массив A:\n" << A << endl;
    cout << "Массив B:\n" << B << endl;

    Vector<Comp> C = (A + B) * A;
    cout << "Массив (A + B) * A:\n" << C << endl;

    return 0;
}