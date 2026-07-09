#include <iostream>
#include "triangle.h"

using namespace std;

int main() {
    cout << "=== Equilateral triangle ===\n";
    BaseTriangle eq(5);
    eq.show();
    eq.show_P();
    eq.show_S();

    cout << "\n=== Isosceles triangle ===\n";
    IsoscelesTriangle iso(6, 10);
    iso.show();
    iso.show_P();
    iso.show_S();

    cout << "\n=== Arbitrary triangle ===\n";
    Triangle t(3, 4, 5);
    t.show();
    t.show_P();
    t.show_S();

    cout << "\n=== Invalid triangle ===\n";
    try {
        Triangle bad(1, 2, 10);
    } catch (...) {
        cout << "Caught exception!\n";
    }

    return 0;
}
