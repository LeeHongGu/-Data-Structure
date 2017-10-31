#include "matrix.h"

int Matrix::getMatrix(int row, int col)
{
	return matrix[row][col];
}
void Matrix::setMatrix(int num, int row, int col)
{
	matrix[row][col] = num;
}

istream& operator >>(istream& is, Matrix& m)
{
	int i, j, n;
	for (i = 1; i <= SIZE; i++)
		for (j = 1; j <= SIZE; j++)
		{
			cin >> n;
			m.setMatrix(n, i - 1, j - 1);
		}

	return is;
}
ostream& operator <<(ostream& os, Matrix& m)
{
	int i, j, width;
	width = m.getElementWidth();

	for (i = 0; i < SIZE; i++)
	{	
		cout << " | ";
		for (j = 0; j < SIZE; j++)
			cout << setw(width) << m.getMatrix(i, j) << " ";
		cout << " |\n";
	}

	return os;
}
Matrix Matrix::operator =(Matrix& m)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			this->matrix[i][j] = m.getMatrix(i, j);

	return *this;
}

bool Matrix::checkNegative()
{
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (matrix[i][j] < 0) return true;
	return false;
}

Matrix Matrix::turnRight()
{
	Matrix result;
	int i, j;

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			result.setMatrix(matrix[i][j], j, SIZE-i-1);

	return result;
}
Matrix Matrix::turnLeft()
{
	Matrix result;
	int i, j;

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			result.setMatrix(matrix[i][j], SIZE - j - 1, i);

	return result;
}

int Matrix::getElementWidth()
{
	int i, j, n = 0;
	int result = 1;
	
	//절댓값이 가장 큰 수 구하기
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (abs(matrix[i][j]) > n) n = abs(matrix[i][j]);

	//자릿수 구하기
	while (n / 10 != 0)
	{
		result++;
		n = n / 10;
	}

	if (checkNegative()) result++;					//음수 포함시 자릿수에 1을 더함
	
	return result;
}
