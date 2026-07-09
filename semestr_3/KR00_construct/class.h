#pragma once

class Class {
private:
    double a, b, c, d;
    double A, B, C, D;
public:
    Class();
    Class(double, double);
    Class(double, double, double);
    Class(double, double, double, double, double, double, double, double);
    void show();
    void set(double, double, double, double);
    double perimeter();
    double area();
    bool isCyclic();
    bool isTangential();
};