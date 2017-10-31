#ifndef __TERM_H__
#define __TERM_H__

class Term
{
	friend class SparseMatrix;

private:
	int row, col;
	double val;

public:
	// ��� operator overloading�� ���
	int getRow() { return row; }			
	int getCol() { return col; }
	double getVal() { return val; }
};

#endif

