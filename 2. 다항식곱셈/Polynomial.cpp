#include "Polynomial.h"

Polynomial::Polynomial()
{
	head = NULL;
}

Polynomial::Polynomial(Polynomial& p)
{
	Term* copyTerm = p.head;
	Term* thisPrev = NULL;

	if (copyTerm)
	{
		head = new Term(p.head->coef, p.head->exp);
		thisPrev = head;
		copyTerm = copyTerm->nextTerm;
	}
	else
	{
		head = NULL;
	}

	while (copyTerm)
	{
		Term* newTerm = new Term(copyTerm->coef, copyTerm->exp);
		
		thisPrev->nextTerm = newTerm;
		thisPrev = newTerm;

		copyTerm = copyTerm->nextTerm;
	}
}

Polynomial::~Polynomial()
{
	Term* curTerm = head;
	Term* nextTemp = NULL;

	while (curTerm)
	{
		nextTemp = curTerm->nextTerm;

		delete curTerm;

		curTerm = nextTemp;
	}
}

void Polynomial::appendTerm(double coef, int exp)
{
	Term* newTerm = new Term(coef, exp);
	Term* curTerm = head;
	Term* preTerm = NULL;

	if (!head)
	{
		head = newTerm;
		return;
	}

	while (curTerm)
	{
		if (newTerm->exp == curTerm->exp)
		{
			double coef = curTerm->coef + newTerm->coef;
			if (coef)
				curTerm->coef = coef;

			return;
		}
		else if (newTerm->exp > curTerm->exp)
		{
			if (curTerm == head)
			{
				newTerm->nextTerm = curTerm;
				head = newTerm;

				return;
			}

			break;
		}

		preTerm = curTerm;
		curTerm = curTerm->nextTerm;
	}

	preTerm->nextTerm = newTerm;
	newTerm->nextTerm = curTerm;
}

Polynomial Polynomial::operator=(Polynomial& p)
{
	this->~Polynomial();

	Term* copyTerm = p.head;
	Term* thisPrev = NULL;

	if (copyTerm)
	{
		head = new Term(p.head->coef, p.head->exp);
		thisPrev = head;
		copyTerm = copyTerm->nextTerm;
	}
	else
	{
		head = NULL;
	}

	while (copyTerm)
	{
		Term* newTerm = new Term(copyTerm->coef, copyTerm->exp);

		thisPrev->nextTerm = newTerm;
		thisPrev = newTerm;

		copyTerm = copyTerm->nextTerm;
	}

	return *this;
}

Polynomial Polynomial::operator+(Polynomial& p)
{
	Term* leftTerm = head;
	Term* rightTerm = p.head;
	Polynomial result;

	while (leftTerm && rightTerm)
	{
		if (leftTerm->exp < rightTerm->exp)
		{
			result.appendTerm(rightTerm->coef, rightTerm->exp);
			rightTerm = rightTerm->nextTerm;
		}
		else if (leftTerm->exp > rightTerm->exp)
		{
			result.appendTerm(leftTerm->coef, leftTerm->exp);
			leftTerm = leftTerm->nextTerm;
		}
		else
		{
			double coef = leftTerm->coef + rightTerm->coef;
			if (coef)
				result.appendTerm(coef, leftTerm->exp);

			leftTerm = leftTerm->nextTerm;
			rightTerm = rightTerm->nextTerm;
		}
	}

	while (leftTerm)
	{
		result.appendTerm(leftTerm->coef, leftTerm->exp);
		leftTerm = leftTerm->nextTerm;
	}
	while (rightTerm)
	{
		result.appendTerm(rightTerm->coef, rightTerm->exp);
		rightTerm = rightTerm->nextTerm;
	}

	return result;
}

Polynomial Polynomial::operator*(Polynomial& p)
{
	Polynomial result;

	Term* leftTerm = head;
	while (leftTerm)
	{
		Polynomial temp;      // 왼쪽 다항식 중 하나의 항과 오른쪽 다항식 모든 항의 곱을 임시저장

		Term* rightTerm = p.head;
		while (rightTerm)
		{
			double coef = leftTerm->coef * rightTerm->coef;
			int exp = leftTerm->exp + rightTerm->exp;

			temp.appendTerm(coef, exp);
			rightTerm = rightTerm->nextTerm;
		}// 오른쪽 다항식 반복종료

		result = result + temp;

		leftTerm = leftTerm->nextTerm;
	}// 왼쪽 다항식 반복종료

	return result;
}

istream& operator >> (istream& is, Polynomial& p)
{
	double coef = 1;
	int exp = 1;

	// 계수나 지수가 0으로 입력되면 종료
	while (coef && exp)
	{
		is >> coef >> exp;

		if (coef)
			p.appendTerm(coef, exp);
	}

	return is;
}

ostream& operator << (ostream& os, const Polynomial& p)
{
	Term* curTerm = p.head;

	// 최고차항은 양수부호없이 출력
	if (curTerm)
	{
		double absCoef = abs(p.head->coef);

		if(p.head->coef < 0)  
			os << " - ";
		if (p.head->exp == 0)					//상수만 출력하는 경우
			os << absCoef;
		else if (absCoef == 1.0)
			os << 'x';							//미지수만 출력하는 경우
		else
			os << absCoef << 'x';
		if (p.head->exp != 1 && p.head->exp)	//exp 1 또는 0인 경우 ^n생략
			os << '^' << p.head->exp;

		curTerm = curTerm->nextTerm;
	}
	else
		os << 0;

	while (curTerm)
	{
		os << *curTerm;
		curTerm = curTerm->nextTerm;
	}

	return os;
}