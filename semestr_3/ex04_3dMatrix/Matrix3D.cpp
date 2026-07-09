#include "Matrix3D.h"
#include <iostream>

using namespace std;

Matrix3D::Matrix3D() {
    for (int i = 0; i < 3; i++) {
        data[i][i] = 1;
    }
}

Matrix3D::Matrix3D(double arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = arr[i][j];
        }
    }
}

void Matrix3D::show() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Matrix3D Matrix3D::T() {
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            double temp = data[i][j];
            data[i][j] = data[j][i];
            data[j][i] = temp;
        }
    }
    return *this;
}

Matrix3D Matrix3D::operator*(const Matrix3D &m) {
    Matrix3D res;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += data[i][k] * m.data[k][j];
            }
            res.data[i][j] = sum;
        }
    }
    return res;
}