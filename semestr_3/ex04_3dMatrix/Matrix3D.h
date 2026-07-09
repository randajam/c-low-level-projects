#pragma once

class Matrix3D {
private:
    double data[3][3]{};
public:
	Matrix3D();
    Matrix3D(double[3][3]);
	void show();
    Matrix3D T();
    Matrix3D operator*(const Matrix3D&);
};