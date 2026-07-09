#pragma once
#include "vector.h"

class Comp : public Vector<double> {
public:
    Comp();
    Comp(double a, double b);
    Comp(const Comp& other);

    Comp& operator=(const Comp& other);
    Comp operator+(const Comp& other) const;
    Comp operator*(const Comp& other) const;
    double& operator[](int i);
    double operator[](int i) const;

    friend std::ostream& operator<<(std::ostream& out, const Comp& other);
    friend std::istream& operator>>(std::istream& in, Comp& other);
};

Comp::Comp(): Vector<double>(2) {}

Comp::Comp(double a, double b): Vector<double>(2) {
    (*this)[0] = a;
    (*this)[1] = b;
}

Comp::Comp(const Comp& other): Vector<double>(other) {}

Comp& Comp::operator=(const Comp& other) {
    Vector<double>::operator=(other);
    return *this;
}

Comp Comp::operator+(const Comp& other) const {
    Comp result(*this);
    for (int i = 0; i < 2; i++) {
        result[i] += other[i];
    }
    return result;
}

Comp Comp::operator*(const Comp& other) const {
    Comp result;
    result[0] = (*this)[0] * other[0] - (*this)[1] * other[1];
    result[1] = (*this)[0] * other[1] + (*this)[1] * other[0];
    return result;
}

double& Comp::operator[](int i) {
    return Vector<double>::operator[](i);
}

double Comp::operator[](int i) const {
    return Vector<double>::operator[](i);
}

std::ostream& operator<<(std::ostream& out, const Comp& comp) {
    out << comp[0] << " " << comp[1];
    return out;
}

std::istream& operator>>(std::istream& in, Comp& comp) {
    in >> comp[0] >> comp[1];
    return in;
}
