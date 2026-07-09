#pragma once
#include <iostream>
#include <cmath>

class BaseTriangle {
protected:
    int a, b, c;
    double S;
    double P;

    bool isTriangle() const {
        return (a+b>c && a+c>b && b+c>a);
    }
    void compute() {
        P = a + b + c;
        double p = P / 2.0;
        S = sqrt(p * (p - a) * (p - b) * (p - c));
    }

public:
    BaseTriangle(int a): a(a), b(a), c(a) {
        if (!isTriangle()) {
            std::cout << "Error: Triangle is not exist" << std::endl;
            exit(1);
        }
        compute();
    }
    BaseTriangle(int a, int b, int c): a(a), b(b), c(c) {
        if (!isTriangle()) {
            std::cout << "Error: Triangle is not exist" << std::endl;
            exit(1);
        }
        compute();
    }

    void show_S() const { std::cout << "Area: " << S << std::endl; }
    void show_P() const { std::cout << "Perimeter: " << P << std::endl; }

    virtual void show() const {
        std::cout << "It's an equilateral triangle. Sides: " << a << std::endl;
    }
};

class IsoscelesTriangle: public BaseTriangle {
public:
    IsoscelesTriangle(int a, int b): BaseTriangle(a, b, b) {}
    void show() const override {
        std::cout << "It's an isosceles triangle. Base: " << a << " Equal sides: " << b << std::endl;
    }
};

class Triangle: public BaseTriangle {
public:
    Triangle(int a, int b, int c): BaseTriangle(a, b, c) {}
    void show() const override {
        std::cout << "It's a triangle. Sides: " << a << " " << b << " " << c << std::endl;
    }
};