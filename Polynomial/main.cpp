#include "Polynomial.h"
using namespace std;

int main()
{
	Polynomial p1, p2;

	cout << "ù��° ���׽��� ���-���� ������ �Է��ϼ���.(������ 0���� �ԷµǸ� ����)\n";
	p1.initPolynomial();

	cout << "�ι�° ���׽��� ���-���� ������ �Է��ϼ���.(������ 0���� �ԷµǸ� ����)\n";
	p2.initPolynomial();

	cout << "�� ���׽��� ���� : " << p1*p2;
	
	return 0;
}