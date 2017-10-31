#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include "Term.h"
#include <iostream>
using namespace std;

const int PRECISION = 2;			// �Ҽ��� ���� ���е�

class SparseMatrix
{
private:
	int rows, cols;
	int termCnt;
	int capacity;
	Term* termsArr;

	void doubleCapacity();
	bool isHaveNegative();					// ���� �� ���� ����
public:
	SparseMatrix();
	SparseMatrix(int rows, int cols);
	SparseMatrix(SparseMatrix& m);
	~SparseMatrix();

	SparseMatrix transposeMatrix();
	int getRows() { return rows; }
	int getCols() { return cols; }
	int getTermsCnt() { return termCnt; }
	Term* getTermsArr() { return termsArr; }

	bool isHaveFraction();					// ���� �� �Ҽ� ����
	int getTermWidth();						// ��½� ������ �ڸ��� ���
	void setMatrix(int rows, int cols);
	void addTerm(int row, int col, double val);

	SparseMatrix& operator=(SparseMatrix& m);
	SparseMatrix operator *(SparseMatrix& m);
};

ostream& operator <<(ostream& os, SparseMatrix& m);

#endif