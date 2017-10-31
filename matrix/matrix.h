#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
using namespace std;

const int SIZE = 4;

class Matrix
{
private:
	int matrix[SIZE][SIZE];
public:
	int getMatrix(int row, int col);
	void setMatrix(int num, int row, int col);

	int getElementWidth();					//가장 긴 원소의 길이 반환
	bool checkNegative();
	Matrix operator =(Matrix& m);
	Matrix turnRight();
	Matrix turnLeft();
};

istream& operator >>(istream& is, Matrix& m);
ostream& operator <<(ostream& os, Matrix& m);
#endif
