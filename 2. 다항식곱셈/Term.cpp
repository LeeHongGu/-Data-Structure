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

	if (t.exp == 0)							//����� ����ϴ� ���
		os << absCoef;
	else if (absCoef == 1.0)
		os << 'x';							//�������� ����ϴ� ���
	else
		os << absCoef << 'x';
	if (t.exp != 1 && t.exp)				//exp 1 �Ǵ� 0�� ��� ^n����
		os << '^' << t.exp;

	return os;
}
