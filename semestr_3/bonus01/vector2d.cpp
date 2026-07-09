#include "vector2d.h"
#include <cmath>
#include <string>

using namespace std;

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::add(Vector2D vector) {
    Vector2D new_vect;
    new_vect.x = this->x + vector.x;
    new_vect.y = this->y + vector.y;
    return new_vect;
}

void Vector2D::add2(Vector2D vector) {
    this->x += vector.x;
    this->y += vector.y;
}

Vector2D Vector2D::sub(Vector2D vector) {
    Vector2D new_vect;
    new_vect.x = this->x - vector.x;
    new_vect.y = this->y - vector.y;
    return new_vect;
}

void Vector2D::sub2(Vector2D vector) {
    this->x -= vector.x;
    this->y -= vector.y;
}

Vector2D Vector2D::mult(double num) {
    Vector2D new_vect;
    new_vect.x = this->x * num;
    new_vect.y = this->y * num;
    return new_vect;
}

void Vector2D::mult2(double num) {
    this->x *= num;
    this->y *= num;
}

string Vector2D::toString() {
    string res = "";
    if (x == 0 && y == 0) {
        res = "0";
    } else {
        res = "(" + to_string(this->x) + "; " + to_string(this->y) + ")";
    }
    return res;
}

double Vector2D::length() {
    double res;
    res = sqrt(pow(this->x, 2) + pow(this->y, 2));
    return res;
}

double Vector2D::scalarProduct(Vector2D vector) {
    if (this->x == 0 && this->y == 0) {
        return 0;
    } else {
        return this->x * vector.x + this->y * vector.y;
    }
}

double Vector2D::cos(Vector2D vector) {
    return this->scalarProduct(vector) / (this->length() * vector.length());
}

bool Vector2D::equals(Vector2D vector) {
    if (this->x == vector.x && this->y == vector.y) {
        return true;
    } else {
        return false;
    }
}