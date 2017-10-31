#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__
#include "CommonHeader.h"
#include "Term.h"

class Polynomial
{
	friend ostream& operator << (ostream& os, const Polynomial& p);
	friend istream& operator >> (istream& is, Polynomial& p);

private:
	Term* head; 

public:
	Polynomial();
	Polynomial(Polynomial& p);
	~Polynomial();
	
	void appendTerm(double coef, int exp);

	Polynomial operator=(Polynomial& p);
	Polynomial operator+(Polynomial& p);
	Polynomial operator*(Polynomial& p);
};


#endif