#include "SparseMatrix.h"
#include <math.h>
#include <iomanip>

// Constructor, Destroyer
SparseMatrix::SparseMatrix()
{
	termCnt = 0;
	capacity = 1;
	termsArr = new Term[capacity];
}

SparseMatrix::SparseMatrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	termCnt = 0;
	capacity = 1;
	termsArr = new Term[capacity];
}

SparseMatrix::SparseMatrix(SparseMatrix& m)
{
	rows = m.rows;
	cols = m.cols;
	termCnt = m.termCnt;
	capacity = m.capacity;
	termsArr = new Term[m.capacity];
	
	for (int i = 0; i < m.termCnt; i++)
	{
		termsArr[i].row = m.termsArr[i].row;
		termsArr[i].col = m.termsArr[i].col;
		termsArr[i].val = m.termsArr[i].val;
	}
}

SparseMatrix:: ~SparseMatrix()
{
	delete[] termsArr;
}

// SparseMatrix Initialize
void SparseMatrix::setMatrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	termCnt = 0;
	capacity = 10;

	if (termsArr != NULL)
		delete[] termsArr;
	termsArr = new Term[capacity];

	double val;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			cin >> val;
			addTerm(i, j, val);
		}
}

// Private Functions
void SparseMatrix::doubleCapacity()
{
	Term* temp = new Term[capacity * 2];

	for (int i = 0; i < termCnt; i++)
		temp[i] = termsArr[i];

	delete[] termsArr;
	termsArr = temp;

	capacity = capacity * 2;
}
bool SparseMatrix::isHaveNegative()
{
	for (int i = 0; i < termCnt; i++)
		if (termsArr[i].val < 0) 
			return true;

	return false;
}

bool SparseMatrix::isHaveFraction()
{
	for (int i = 0; i < termCnt; i++)
	{
		double absNum = abs(termsArr[i].val);
		int intPart = absNum / 1;

		if ( (absNum - intPart) > 0 )
			return true;
	}

	return false;
}

// Public Functions
void SparseMatrix::addTerm(int row, int col, double val)
{
	if (!val)				// 0�� �ƴ� �׸� ����
		return;
	if (termCnt == capacity)
		doubleCapacity();

	termsArr[termCnt].row = row;
	termsArr[termCnt].col = col;
	termsArr[termCnt++].val = val;
}

SparseMatrix SparseMatrix::transposeMatrix()
{
	SparseMatrix result(cols, rows);
	result.termCnt = termCnt;
	int* rowIndex = new int[cols];
	int rowIndexTemp;

	// ���� ���ٸ� �Լ�����
	if (termCnt == 0)
		return *this;

	// ��������� termsArr �ε��������� �°� result�� capacity�� termsArrũ�� ����
	if (result.capacity != capacity)
	{
		delete[] result.termsArr;
		result.termsArr = new Term[capacity];
		result.capacity = capacity;
	}

	// 0 �ʱ�ȭ
	for (int i = 0; i < cols; i++)
		rowIndex[i] = 0;

	// �� ������ġ ���
	for (int i = 0; i < termCnt; i++)
		rowIndex[termsArr[i].col]++;

	// ���� ������ �� ������ġ ���
	rowIndexTemp = rowIndex[0];
	rowIndex[0] = 0;
	for (int i = 1; i < cols; i++)
	{
		int temp = rowIndex[i];
		rowIndex[i] = rowIndex[i - 1] + rowIndexTemp;
		rowIndexTemp = temp;
	}

	// ��ġ��� �� �켱���� ��ġ
	for (int i = 0; i < termCnt; i++)
	{
		int row = rowIndex[termsArr[i].col];
		result.termsArr[row].row = termsArr[i].col;
		result.termsArr[row].col = termsArr[i].row;
		result.termsArr[row].val = termsArr[i].val;
		rowIndex[termsArr[i].col]++;						// �� ������ġ ����
	}
	delete[] rowIndex;

	return result;
}

int SparseMatrix::getTermWidth()
{
	int result = 1;
	int n = 0;

	// ������ ������ ���� ū �� ���ϱ�
	for (int i = 0; i < termCnt; i++)
		if (abs(termsArr[i].val) > n) 
			n = abs(termsArr[i].val);

	// ������ �ڸ��� ���ϱ�
	while (n / 10 != 0)
	{
		result++;
		n = n / 10;
	}

	// ���� ���Խ� �ڸ����� 1�� ����
	if (isHaveNegative()) result++;

	return result;
}

// Operator Overloadings
SparseMatrix& SparseMatrix::operator=(SparseMatrix& m)
{
	Term* temp = new Term[m.capacity];
	termCnt = m.termCnt;
	rows = m.rows;
	cols = m.cols;
	capacity = m.capacity;

	for (int i = 0; i < m.termCnt; i++)
	{
		temp[i].row = m.termsArr[i].row;
		temp[i].col = m.termsArr[i].col;
		temp[i].val = m.termsArr[i].val;
	}

	delete[] this->termsArr;
	this->termsArr = temp;

	return *this;
}

SparseMatrix SparseMatrix::operator *(SparseMatrix& m)
{
	SparseMatrix trMatrix = m.transposeMatrix();
	SparseMatrix result(rows, m.cols);
	
	// operand �����˻�
	if (cols != m.rows)
	{
		cout << "����� ������ �Ұ����մϴ�.\n";
		return result;
	}

	// ������Ǽ���
	if (termCnt == capacity)
		doubleCapacity();
	if (trMatrix.termCnt == trMatrix.capacity)
		trMatrix.doubleCapacity();
	termsArr[termCnt].row = rows;
	trMatrix.termsArr[trMatrix.termCnt].row = trMatrix.rows;
	trMatrix.termsArr[trMatrix.termCnt].col = -1;

	int preMatrixRowExp = 0;								// �� ��� row ������� ���
	int preMatrixIndex = 0;									// �� ��� terms ������
	int postMatrixIndex = 0;								// �� ��� terms ������
	int resultRowPos = termsArr[0].row;						// ������ row��
	int resultColPos = trMatrix.termsArr[0].row;			// ������ row��
	double rowSum = 0.0;

	while (preMatrixIndex < termCnt)						// �� ��� ���پ� row ���, ������ ��ü ���
	{
		postMatrixIndex = 0;								// �� ��� ��� �˻��ϵ��� �ʱ�ȭ
		resultColPos = trMatrix.termsArr[0].row;			// �������� col�� �ʱ�ȭ
		while (postMatrixIndex <= trMatrix.termCnt)			// �� ��� ������ row���, ������ ������ row ���
		{
			// �� ��� 1���� �˻�Ϸ�
			if (termsArr[preMatrixIndex].row != resultRowPos)
			{
				result.addTerm(resultRowPos, resultColPos, rowSum);
				rowSum = 0.0;
				preMatrixIndex = preMatrixRowExp;

				// colPos ����
				while (trMatrix.termsArr[postMatrixIndex].row == resultColPos)
					postMatrixIndex++;
				resultColPos = trMatrix.termsArr[postMatrixIndex].row;
			}

			// �� ��� ������ �˻�Ϸ�
			else if (trMatrix.termsArr[postMatrixIndex].row != resultColPos)
			{
				result.addTerm(resultRowPos, resultColPos, rowSum);
				rowSum = 0.0;
				preMatrixIndex = preMatrixRowExp;
				resultColPos = trMatrix.termsArr[postMatrixIndex].row;
			}

			// �� ��� col ũ�� �� ����� ���� term ����
			else if (termsArr[preMatrixIndex].col < trMatrix.termsArr[postMatrixIndex].col)
				preMatrixIndex++;

			// �� ����� col�� �� ����� col�� ��ġ�� ���� ���� ���� & ���� ���� term ����
			else if (termsArr[preMatrixIndex].col == trMatrix.termsArr[postMatrixIndex].col)
			{
				rowSum = rowSum + termsArr[preMatrixIndex].val * trMatrix.termsArr[postMatrixIndex].val;
				preMatrixIndex++;
				postMatrixIndex++;
			}

			// �� ����� col ũ�� �� ����� ���� term ����
			else
				postMatrixIndex++;
		}

		//  rowPos ����
		while (termsArr[preMatrixIndex].row == resultRowPos)
			preMatrixIndex++;
		
		resultRowPos = termsArr[preMatrixIndex].row;
		preMatrixRowExp = preMatrixIndex;					// ������� Ȯ���� �� ��� row�� ���
	}
	return result;
}

ostream& operator <<(ostream& os, SparseMatrix& m)
{
	Term* temp = m.getTermsArr();
	int cnt = 0;
	int precision = 0;
	int width = m.getTermWidth();

	if (m.isHaveFraction())
	{
		os.setf(ios::fixed);
		os.setf(ios::showpoint);
		os.precision(PRECISION);
		width = width + PRECISION + 1;				// precision + dot
	}
	
	for (int i = 0; i < m.getRows(); i++)
	{
		os << " | ";
		for (int j = 0; j < m.getCols(); j++)
		{
			if((temp[cnt].getRow() == i) && (temp[cnt].getCol() == j))
				os <<  setw(width) << temp[cnt++].getVal() << " ";
			else
				os << setw(width) << "0" << " ";
		}
		os << "|\n";
	}

	return os;
}
