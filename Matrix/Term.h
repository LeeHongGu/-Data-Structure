#ifndef __TERM_H__
#define __TERM_H__

class Term
{
	friend class SparseMatrix;

private:
	int row, col;
	double val;

public:
	// 출력 operator overloading에 사용
	int getRow() { return row; }			
	int getCol() { return col; }
	double getVal() { return val; }
};

#endif

