#include "SparseMatrix.h"

int main()
{
	SparseMatrix m1, m2;
	int m, n, p;

	cout << "곱할 행렬이 mxn 와 nxp 크기일 때, m과 n과 p의 값을 순서대로 입력하세요 : ";
	cin >> m >> n >> p;
	
	if (m <= 0 || n <= 0 || p <= 0)
	{
		cout << "0개의 행(열)을 가진 행렬을 생성할 수 없습니다.\n";
		return 0;
	}

	cout << "첫번째 행렬의 " << m*n << "개 값을 행우선으로 입력하세요 : ";
	m1.setMatrix(m, n);

	cout << "두번째 행렬의 " << n*p << "개 값을 행우선으로 입력하세요 : ";
	m2.setMatrix(n, p);
	
	cout << "곱셈 결과\n";
	cout << m1*m2;

	return 0;
}