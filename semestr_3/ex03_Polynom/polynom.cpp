#include "polynom.h"

#include <iostream>

using namespace std;

Polynom::Polynom() {
    for (int i = 0; i < 6; i++) {
        this->coef[i] = 0;
    }
}

Polynom::Polynom(int array[6]) {
    for (int i = 0; i < 6; i++) {
        this->coef[i] = array[i];
    }
}

void Polynom::Show() {
    for (int i = 5; i >= 0; i--) {
        if (this->coef[i] == 0) {
            continue;
        }
        cout << this->coef[i] << "x^" << i << " ";
    }
    cout << endl;
}

void Polynom::Set(int idx, int a) {
    if (idx <= 5) { 
        this->coef[idx] = a;
    }
}

Polynom Polynom::operator+(const Polynom &p) {
    Polynom res;
    for (int i = 0; i < 6; i++) {
        res.coef[i] = this->coef[i] + p.coef[i];
    }
    return res;
}

Polynom Polynom::operator-(const Polynom &p) {
    Polynom res;
    for (int i = 0; i < 6; i++) {
        res.coef[i] = this->coef[i] - p.coef[i];
    }
    return res;
}

Polynom Polynom::operator*(int k) {
    Polynom res;
    for (int i = 0; i < 6; i++) {
        res.coef[i] = this->coef[i] * k;
    }
    return res;
}

Polynom Polynom::operator*(const Polynom &p) {
    Polynom res;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i + j <= 5) {
                res.coef[i + j] += this->coef[i] * p.coef[j];
            }
        }
    }
    return res;
}

bool Polynom::operator==(const Polynom &p) {
    for (int i = 0; i < 6; i++) {
        if (this->coef[i] != p.coef[i]) {
            return false;
        }
    }
    return true;
}

Polynom Polynom::operator=(const Polynom &p) {
    for (int i = 0; i < 6; i++) {
        this->coef[i] = p.coef[i];
    }
    return *this;
}