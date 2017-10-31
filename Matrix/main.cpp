#include "SparseMatrix.h"

int main()
{
	SparseMatrix m1, m2;
	int m, n, p;

	cout << "���� ����� mxn �� nxp ũ���� ��, m�� n�� p�� ���� ������� �Է��ϼ��� : ";
	cin >> m >> n >> p;
	
	if (m <= 0 || n <= 0 || p <= 0)
	{
		cout << "0���� ��(��)�� ���� ����� ������ �� �����ϴ�.\n";
		return 0;
	}

	cout << "ù��° ����� " << m*n << "�� ���� ��켱���� �Է��ϼ��� : ";
	m1.setMatrix(m, n);

	cout << "�ι�° ����� " << n*p << "�� ���� ��켱���� �Է��ϼ��� : ";
	m2.setMatrix(n, p);
	
	cout << "���� ���\n";
	cout << m1*m2;

	return 0;
}