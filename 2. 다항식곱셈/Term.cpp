#include "Term.h"

Term::Term(double coef, int exp)
{
	this->coef = coef;
	this->exp = exp;

	nextTerm = NULL;
}

ostream & operator<<(ostream & os, const Term & t)
{
	double absCoef = abs(t.coef);

	(t.coef > 0) ? (os << " + ") : (os << " - ");

	if (t.exp == 0)							//상수만 출력하는 경우
		os << absCoef;
	else if (absCoef == 1.0)
		os << 'x';							//미지수만 출력하는 경우
	else
		os << absCoef << 'x';
	if (t.exp != 1 && t.exp)				//exp 1 또는 0인 경우 ^n생략
		os << '^' << t.exp;

	return os;
}
