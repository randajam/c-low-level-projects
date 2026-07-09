#include "class.h"
#include <iostream>

using namespace std;

int main() {
    Class c1, c2(3, 40), c3(3, 4, 20), c4(3, 4, 5, 6, 100, 110, 205, 45);
    cout << "Class c1: " << endl;
    c1.show();
    cout << "Class c2: " << endl;
    c2.show();
    cout << "Class c3: " << endl;
    c3.show();
    cout << "Class c4: " << endl;
    c4.show();
    c4.set(5, 5, 1, 2);
    c4.show();
    cout << "Area of c3: " << c3.area() << endl;
    cout << "Perimeter of c3: " << c3.perimeter() << endl;
    cout << "c3 is cyclical? " << (c3.isCyclic() ? "true" : "false") << endl;
    cout << "c3 is tangential? " << (c3.isTangential() ? "true" : "false") << endl;
    cout << "c2 is cyclical? " << (c2.isCyclic() ? "true" : "false") << endl;
    cout << "c2 is tangential? " << (c2.isTangential() ? "true" : "false") << endl;
    return 0;
}