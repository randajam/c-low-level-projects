#include "polynom.h"
#include <iostream>

using namespace std;

int main() {
    int a[6] = {1, 2, 3, 4, 5, 6};
    Polynom p1, p2(a);
    p1.Set(1, 2);
    p1.Set(2, 3);
    p1.Set(3, -4);
    p1.Set(4, 5);
    p1.Set(5, -6);

    p1.Show();
    p2.Show();

    Polynom op;
    op = p1 * p2;
    cout << "Mul:" << endl;
    op.Show();
    op = p1 + p2;
    cout << "Sum:" << endl;
    op.Show();
    op = p1 - p2;
    cout << "Min:" << endl;
    op.Show();
    op = p1 * 2;
    cout << "Mul 2:" << endl;
    op.Show();
    op = p1;
    cout << "Eq:" << endl;
    op.Show();
}