#include "triangle.h"
#include <iostream>
#include <cmath>

using namespace std;

bool Triangle::isTriangle(double A, double B, double C) {
    if (A + B > C && A + C > B && B + C > A) {
        return true;
    }
    return false;
}

Triangle::Triangle(void) {
    this->a = 1;
    this->b = 1;
    this->c = 1;
}

Triangle::Triangle(double A, double B, double C) {
    if (isTriangle(A, B, C)) {
        this->a = A;
        this->b = B;
        this->c = C;
    } else if (C == 0) {
        if (2 * A > B) {
            this->a = A;
            this->b = A;
            this->c = B;
        } else if (2 * B > A) {
            this->a = B;
            this->b = B;
            this->c = A;
        } else {
            this->a = 1;
            this->b = 1;
            this->c = 1;
        }
    } 
    else {
        this->a = 1;
        this->b = 1;
        this->c = 1;
    }
}

Triangle::Triangle(double A, double B) {
    this->a = A;
    this->b = B;
    c = sqrt(this->a * this->a + this->b * this->b);
}

Triangle::Triangle(double A) {
    if (A > 0) {
        this->a = A;
        this->b = A;
        this->c = A;
    } else {
        this->a = 1;
        this->b = 1;
        this->c = 1;
    }
}

void Triangle::Show() {
    cout << this->a << " " << this->b << " " << this->c << endl;
}

void Triangle::SetA(double A) {
    this->a = A;
}
void Triangle::SetB(double B) {
    this->b = B;
}
void Triangle::SetC(double C) {
    this->c = C;
}
double Triangle::GetA() {
    return this->a;
}
double Triangle::GetB() {
    return this->b;
}
double Triangle::GetC() {
    return this->c;
}
double Triangle::GetPerimeter() {
    return this->a + this->b + this->c;
}
double Triangle::GetArea() {
    double p = (this->a + this->b + this->c) / 2;
    return sqrt(p * (p - this->a) * (p - this->b) * (p - this->c));
}

double Triangle::GetRadiusIn() {
    double p = (this->a + this->b + this->c) / 2;
    return 2 * GetArea() / p;
}
double Triangle::GetRadiusOut() {
    return this->a*this->b*this->c / (4 * GetArea());
}
