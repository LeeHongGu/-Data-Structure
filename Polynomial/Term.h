#ifndef __TERM_H__
#define __TERM_H__

class Term
{
	friend class Polynomial;

private:
	double coef;
	int exp;

public:
	// 출력 operator overloading에 사용
	double getCoef() { return coef; }
	int getExp() { return exp; }
};

#endif
