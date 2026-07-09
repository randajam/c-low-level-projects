#include "rational.h"

#include <iostream>
#include <numeric>

using namespace std;

Rational::Rational() {
    this->integer = 0;
    this->numerator = 0;
    this->denominator = 1;
}

Rational::Rational(int integer, int numerator, int denominator) {
    if (denominator == 0) {
        cout << "Error: denominator = 0" << endl;
        exit(1);
    }
    this->integer = integer;
    this->numerator = numerator;
    this->denominator = denominator;
    
    this->normalize();
}

void Rational::Set(int integer, int numerator, int denominator) {
    if (denominator == 0) {
        cout << "Error: denominator = 0" << endl;
        exit(1);
    } else {
        this->integer = integer;
        this->numerator = numerator;
        this->denominator = denominator;
    }
}

void Rational::Show() {
    if (this->integer != 0) {
        cout << this->integer << " " << this->numerator << "/" << this->denominator << endl;
    } else {
        cout << this->numerator << "/" << this->denominator << endl;
    }
}

void Rational::to_improper() {
    this->numerator += abs(this->integer) * this->denominator;
    if (this->integer < 0) {
        this->numerator *= -1;
    }
    this->integer = 0;
}

void Rational::normalize() {
    bool is_negative = false;

    if (this->numerator < 0 || this->integer < 0) {
        is_negative = true;
    }
    
    this->integer = abs(this->integer) + abs(this->numerator / this->denominator);
    this->numerator = abs(this->numerator) % abs(this->denominator);

    int GCD = gcd(this->numerator, this->denominator);
    this->numerator /= GCD;
    this->denominator /= GCD;

    if (is_negative) {
        if (this->integer == 0) {
            this->numerator *= -1;
        } else {
            this->integer *= -1;
        }
    }
}


void Rational::Add(Rational a) {
    this->to_improper();
    a.to_improper();

    this->numerator = this->numerator * a.denominator + a.numerator * this->denominator;
    this->denominator *= a.denominator;

    this->normalize();
}

void Rational::Sub(Rational a) {
    this->to_improper();
    a.to_improper();

    this->numerator = this->numerator * a.denominator - a.numerator * this->denominator;
    this->denominator *= a.denominator;

    this->normalize();
}

void Rational::Mul(Rational a) {
    this->to_improper();
    a.to_improper();

    this->numerator *= a.numerator;
    this->denominator *= a.denominator;

    this->normalize();
}

void Rational::Div(Rational a) {
    this->to_improper();
    a.to_improper();
    
    this->numerator *= a.denominator;
    this->denominator *= abs(a.numerator);
    if (a.numerator < 0) {
        this->numerator *= -1;
    }
    this->normalize();
}