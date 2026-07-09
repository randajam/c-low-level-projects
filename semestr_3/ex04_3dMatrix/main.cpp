#include "Matrix3D.h"
#include <iostream>

using namespace std;

int main() {
    double arr[3][3] = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    Matrix3D m1;
    Matrix3D m2(arr);
    m1.show();
    m2.show();
    m2.T();
    m2.show();
    Matrix3D m3 = m1 * (m2 * m2.T());
    m3.show();
    return 0;
}