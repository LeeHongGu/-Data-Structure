#include "Polynomial.h"
#include "CommonHeader.h"

int main()
{
	Polynomial p1, p2;

	cout << "첫번째 다항식을 계수-지수 쌍으로 입력하세요.(계수나 지수가 0으로 입력되면 종료)" << endl;
	cin >> p1;

	cout << "두번째 다항식을 계수-지수 쌍으로 입력하세요.(계수나 지수가 0으로 입력되면 종료)" << endl;
	cin >> p2;

	cout << "두 다항식의 곱은 : " << p1*p2 << endl;

	return 0;
}