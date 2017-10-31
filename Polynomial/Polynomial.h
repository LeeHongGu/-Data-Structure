#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "Term.h"
#include <iostream>
using namespace std;
const int DEFAULT_CAPACITY = 10;

class Polynomial
{
private:
	int capacity;
	int termCnt;
	Term* termsArr;
public:
	Polynomial();
	Polynomial(Polynomial &p);
	~Polynomial();

	int getTermCnt() { return termCnt; }
	int getCapacity() { return capacity; }
	double getCoefAt(int index) { return termsArr[index].coef; }
	int getExpAt(int index) { return termsArr[index].exp; }

	void addTerm(double coef, int exp);
	void initPolynomial();
	void doubleCapacity();

	Polynomial& operator =(Polynomial& p);
	Polynomial operator +(Polynomial& p);
	Polynomial operator *(Polynomial& p);
};

ostream& operator <<(ostream &os, Polynomial &p);
#endif
