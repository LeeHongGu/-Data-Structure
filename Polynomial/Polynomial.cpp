#include "Polynomial.h"
#include <math.h>

// Constructor, Destroyer
Polynomial::Polynomial()
{
	termCnt = 0;
	capacity = DEFAULT_CAPACITY;
	termsArr = new Term[capacity];
}

Polynomial::Polynomial(Polynomial &p)
{
	termCnt = p.termCnt;
	capacity = p.capacity;

	termsArr = new Term[p.capacity];
	for (int i = 0; i < p.termCnt; i++)
	{
		termsArr[i].coef = p.termsArr[i].coef;
		termsArr[i].exp = p.termsArr[i].exp;
	}
}

Polynomial::~Polynomial()
{
	delete[] termsArr;
}

// Public Functions
void Polynomial::addTerm(double coef, int exp)
{
	if (coef == 0)
		return;
	if (capacity == termCnt)
		doubleCapacity();
	termsArr[termCnt].coef = coef;
	termsArr[termCnt++].exp = exp;
}

void Polynomial::initPolynomial()
{
	double coef;
	int exp = 1;

	while (exp != 0)
	{
		cin >> coef >> exp;
		addTerm(coef, exp);
	}
}

void Polynomial::doubleCapacity()
{
	Term* temp = new Term[capacity * 2];
	for (int i = 0; i < capacity; i++)
	{
		temp[i].coef = termsArr[i].coef;
		temp[i].exp = termsArr[i].exp;
	}

	delete[] termsArr;
	termsArr = temp;
	capacity = capacity * 2;
}

// Operator Overloadings
Polynomial& Polynomial::operator =(Polynomial& p)
{
	Term* temp = new Term[p.capacity];
	capacity = p.capacity;
	termCnt = p.termCnt;

	for (int i = 0; i < p.termCnt; i++)
	{
		temp[i].coef = p.termsArr[i].coef;
		temp[i].exp = p.termsArr[i].exp;
	}

	delete[] termsArr;
	termsArr = temp;

	return *this;
}

Polynomial Polynomial::operator +(Polynomial& p)
{
	Polynomial result;

	int l_pos = 0, r_pos = 0;
	while ((l_pos < termCnt) && (r_pos<p.getTermCnt()))
	{
		if (getExpAt(l_pos) > p.getExpAt(r_pos))
		{
			result.addTerm(getCoefAt(l_pos), getExpAt(l_pos));
			l_pos++;
		}
		else if (getExpAt(l_pos) < p.getExpAt(r_pos))
		{
			result.addTerm(p.getCoefAt(r_pos), p.getExpAt(r_pos));
			r_pos++;
		}
		else
		{
			double coef = getCoefAt(l_pos) + p.getCoefAt(r_pos);
			if(coef)												//계수의 합 0인경우 생략
				result.addTerm(coef, getExpAt(l_pos));
			l_pos++;
			r_pos++;
		}
	}

	for(;l_pos<termCnt; l_pos++)
		result.addTerm(getCoefAt(l_pos), getExpAt(l_pos));
	for(;r_pos<p.getTermCnt(); r_pos++)
		result.addTerm(p.getCoefAt(r_pos), p.getExpAt(r_pos));

	return result;
}

Polynomial Polynomial::operator *(Polynomial& p)
{
	Polynomial result;
	double coef;
	int exp;

	for (int i = 0; i < termCnt; i++)
	{
		Polynomial temp;
		coef = getCoefAt(i);
		exp = getExpAt(i);
		for (int j = 0; j < p.termCnt; j++)
		{
			temp.addTerm(coef*p.getCoefAt(j), exp + p.getExpAt(j));
		}
		result = result + temp;
	}

	return result;
}

ostream& operator <<(ostream &os, Polynomial &p)
{
	bool print_exp = false;			

	for (int i = 0; i < p.getTermCnt(); i++)
	{
		double coef = p.getCoefAt(i);
		int exp = p.getExpAt(i);

		if (coef > 0)
		{
			if (print_exp)						// 가장 앞 양수부호 생략
				os << " + ";
			if (exp == 0)						//상수만 출력하는 경우
				os << coef;
			else if (coef == 1)
				os << "x";					//미지수만 출력하는 경우
			else
				os << coef << "x";
			if(exp>1)							//exp 1이하인 경우 ^n생략
				os << "^" << exp;
			print_exp = true;
		}
		else if (coef < 0)
		{
			os << " - ";
			if (exp == 0)						//상수만 출력하는 경우
				os << abs(coef);
			else if (coef == -1)
				os << "x";					//미지수만 출력하는 경우
			else
				os << abs(coef) << "x";
			if (exp>1)							//exp 1이하인 경우 ^n생략
				os << "^" << exp;
			print_exp = true;
		}
	}
	if (!print_exp) os << 0;					//계수가모두 0이라면 0출력
	os << endl;

	return os;
}