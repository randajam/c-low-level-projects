#pragma once

class Rational
{
private:
    int integer;
	int numerator;
	int denominator;
public:
	Rational();
	Rational(int integer, int numerator, int denominator);
	void Set(int integer, int numerator, int denominator);
	void Show();
	
	void to_improper();
	void normalize();

	void Add(Rational);
	void Sub(Rational);
	void Mul(Rational);
	void Div(Rational);
};