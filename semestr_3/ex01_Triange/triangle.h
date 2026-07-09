#pragma once

class Triangle {
private:
    double a;
    double b;
    double c;

public:
    bool isTriangle(double, double, double);
    Triangle(void);
    Triangle(double, double, double);
    Triangle(double, double);
    Triangle(double);
    void Show();
    void SetA(double A);
    void SetB(double B);
    void SetC(double C);
    double GetA();
    double GetB();
    double GetC();
    double GetPerimeter();
    double GetArea();
    double GetRadiusOut();
    double GetRadiusIn();
};
