#include "Polynomial.h"
using namespace std;

int main()
{
	Polynomial p1, p2;

	cout << "첫번째 다항식을 계수-지수 쌍으로 입력하세요.(지수가 0으로 입력되면 종료)\n";
	p1.initPolynomial();

	cout << "두번째 다항식을 계수-지수 쌍으로 입력하세요.(지수가 0으로 입력되면 종료)\n";
	p2.initPolynomial();

	cout << "두 다항식의 곱은 : " << p1*p2;
	
	return 0;
}