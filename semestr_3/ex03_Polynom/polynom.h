#pragma once

class Polynom {
private:
    int coef[6];
public:
    Polynom();
    Polynom(int array[6]);
    void Show();
    void Set(int idx, int a);
    Polynom operator+(const Polynom &p);
    Polynom operator-(const Polynom &p);
    Polynom operator*(int k);
    Polynom operator*(const Polynom &p);
    bool operator==(const Polynom &p);
    Polynom operator=(const Polynom &p);
};    
