#pragma once

#include <string>

using namespace std;

class Vector2D {
private:
	double x;
	double y;
public:
	Vector2D();
	Vector2D(double, double);
	Vector2D add(Vector2D); //
    void add2(Vector2D);
    Vector2D sub(Vector2D); // 
    void sub2(Vector2D);
    Vector2D mult(double); //
    void mult2(double);
    string toString(); //
    double length(); //
    double scalarProduct(Vector2D); //
    double cos(Vector2D); //
    bool equals(Vector2D); //
};