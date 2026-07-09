#include "vector2d.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Vector2D v1(1, 2), v2(3, 4), v3(5, 6);

    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v3 = " << v3.toString() << endl;

    cout << "v1 + v2 = " << (v1.add(v2)).toString() << endl;
    cout << "v1 - v3 = " << (v1.sub(v3)).toString() << endl;
    cout << "v1 * 3 = " << (v1.mult(3)).toString() << endl;
    cout << "length of v1 = " << v1.length() << endl;
    cout << "length of v2 = " << v2.length() << endl;
    cout << "length of v3 = " << v3.length() << endl;
    cout << "cos between v1 and v2 = " << v1.cos(v2) << endl;
    cout << "scalar product of v1 and v2 = " << v1.scalarProduct(v2) << endl;
    cout << "v1 == v2 ? " << (v1.equals(v2) ? "true" : "false") << endl;
    cout << "v1 == v1 ? " << (v1.equals(v1) ? "true" : "false") << endl;
}