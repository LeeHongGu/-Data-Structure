#ifndef __TERM_H__
#define __TERM_H__

class Term
{
	friend class Polynomial;

private:
	double coef;
	int exp;

public:
	// ��� operator overloading�� ���
	double getCoef() { return coef; }
	int getExp() { return exp; }
};

#endif
