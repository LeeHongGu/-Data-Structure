#ifndef __TERM_H__
#define __TERM_H__
#include "CommonHeader.h"
#include <math.h>

class Term
{
	friend class Polynomial;
	friend ostream& operator << (ostream& os, const Term& t);
	friend ostream& operator << (ostream& os, const Polynomial& t);		// 최고차항 별도 출력을 위해

private:

	double coef;
	int exp;
	Term* nextTerm;

public:
	Term(double coef = 0.0, int exp = 0);

};

#endif