#include "class.h"
#include <cmath>
#include <iostream>

using namespace std;

Class::Class() {
    this->a = 1;
    this->b = 1;
    this->c = 1;
    this->d = 1;

    this->A = 90;
    this->B = 90;
    this->C = 90;
    this->D = 90;
}

Class::Class(double x, double ang) {
    /*Squared or rombik construct*/
    this->a = x;
    this->b = x;
    this->c = x;
    this->d = x;

    this->A = ang;
    this->B = 180 - ang;
    this->C = ang;
    this->D = 180 - ang;
}

Class::Class(double x, double y, double ang) {
    this->a = x;
    this->b = y;
    this->c = x;
    this->d = y;

    this->A = ang;
    this->B = 180 - ang;
    this->C = ang;
    this->D = 180 - ang;
}

Class::Class(double x, double y, double z, double t, double X, double Y, double Z, double T) {
    this->a = x;
    this->b = y;
    this->c = z;
    this->d = t;

    this->A = X;
    this->B = Y;
    this->C = Z;
    this->D = T;
}

void Class::show() {
    cout << this->a << " " << this->b << " " << this->c << " " << this->d << endl;
    cout << this->A << " " << this->B << " " << this->C << " " << this->D << endl;
}

void Class::set(double a, double b, double c, double d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

double Class::perimeter() {
    return this->a + this->b + this->c + this->d;
}

double Class::area() {
    if (this->A == 90 && this->B == 90 && this->C == 90 && this->D == 90) {
        return this->a * this->b;
    }
    else if (this->A == this->C && this->B == this->D) {
        return this->a * this->b * sin(this->A * M_PI / 180) / 2;
    }
    return 0;
}

bool Class::isCyclic() {
    if ((this->A + this->C) == 180 && (this->B + this->D) == 180) {
        return true;
    } 
    return false;
}

bool Class::isTangential() {
    if ((this->a + this->c) == (this->b + this->d)) {
        return true;
    }
    return false;
}