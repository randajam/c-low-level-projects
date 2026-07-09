#include "rational.h"

#include <iostream>

using namespace std;

int main() {
    Rational r1(-3, 42, 5), r2(-2, 2, 7), r3(1, 4, 5);
    
    r1.Show();
    r2.Show();

    r1.Add(r2);
    r1.Show();

    r1.Sub(r2);
    r1.Show();

    r1.Mul(r2);
    r1.Show();

    r1.Div(r2);
    r1.Show();
    
    return 0;
}