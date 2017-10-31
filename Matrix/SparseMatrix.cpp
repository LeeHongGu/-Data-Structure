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
	if (!val)				// 0이 아닌 항만 저장
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

	// 항이 없다면 함수종료
	if (termCnt == 0)
		return *this;

	// 원본행렬의 termsArr 인덱스범위에 맞게 result의 capacity와 termsArr크기 조정
	if (result.capacity != capacity)
	{
		delete[] result.termsArr;
		result.termsArr = new Term[capacity];
		result.capacity = capacity;
	}

	// 0 초기화
	for (int i = 0; i < cols; i++)
		rowIndex[i] = 0;

	// 행 시작위치 계산
	for (int i = 0; i < termCnt; i++)
		rowIndex[termsArr[i].col]++;

	// 이전 열값의 행 시작위치 계산
	rowIndexTemp = rowIndex[0];
	rowIndex[0] = 0;
	for (int i = 1; i < cols; i++)
	{
		int temp = rowIndex[i];
		rowIndex[i] = rowIndex[i - 1] + rowIndexTemp;
		rowIndexTemp = temp;
	}

	// 전치행렬 행 우선으로 전치
	for (int i = 0; i < termCnt; i++)
	{
		int row = rowIndex[termsArr[i].col];
		result.termsArr[row].row = termsArr[i].col;
		result.termsArr[row].col = termsArr[i].row;
		result.termsArr[row].val = termsArr[i].val;
		rowIndex[termsArr[i].col]++;						// 행 시작위치 조정
	}
	delete[] rowIndex;

	return result;
}

int SparseMatrix::getTermWidth()
{
	int result = 1;
	int n = 0;

	// 정수부 절댓값이 가장 큰 수 구하기
	for (int i = 0; i < termCnt; i++)
		if (abs(termsArr[i].val) > n) 
			n = abs(termsArr[i].val);

	// 정수부 자릿수 구하기
	while (n / 10 != 0)
	{
		result++;
		n = n / 10;
	}

	// 음수 포함시 자릿수에 1을 더함
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
	
	// operand 차원검사
	if (cols != m.rows)
	{
		cout << "행렬의 곱셈이 불가능합니다.\n";
		return result;
	}

	// 경계조건설정
	if (termCnt == capacity)
		doubleCapacity();
	if (trMatrix.termCnt == trMatrix.capacity)
		trMatrix.doubleCapacity();
	termsArr[termCnt].row = rows;
	trMatrix.termsArr[trMatrix.termCnt].row = trMatrix.rows;
	trMatrix.termsArr[trMatrix.termCnt].col = -1;

	int preMatrixRowExp = 0;								// 앞 행렬 row 연산수행 기억
	int preMatrixIndex = 0;									// 앞 행렬 terms 참조값
	int postMatrixIndex = 0;								// 뒷 행렬 terms 참조값
	int resultRowPos = termsArr[0].row;						// 결과행렬 row값
	int resultColPos = trMatrix.termsArr[0].row;			// 결과행렬 row값
	double rowSum = 0.0;

	while (preMatrixIndex < termCnt)						// 앞 행렬 한줄씩 row 사용, 결과행렬 전체 계산
	{
		postMatrixIndex = 0;								// 뒷 행렬 모두 검사하도록 초기화
		resultColPos = trMatrix.termsArr[0].row;			// 결과행렬의 col값 초기화
		while (postMatrixIndex <= trMatrix.termCnt)			// 앞 행렬 한줄의 row사용, 결과행렬 한줄의 row 계산
		{
			// 앞 행렬 1개행 검사완료
			if (termsArr[preMatrixIndex].row != resultRowPos)
			{
				result.addTerm(resultRowPos, resultColPos, rowSum);
				rowSum = 0.0;
				preMatrixIndex = preMatrixRowExp;

				// colPos 증가
				while (trMatrix.termsArr[postMatrixIndex].row == resultColPos)
					postMatrixIndex++;
				resultColPos = trMatrix.termsArr[postMatrixIndex].row;
			}

			// 뒷 행렬 끝까지 검사완료
			else if (trMatrix.termsArr[postMatrixIndex].row != resultColPos)
			{
				result.addTerm(resultRowPos, resultColPos, rowSum);
				rowSum = 0.0;
				preMatrixIndex = preMatrixRowExp;
				resultColPos = trMatrix.termsArr[postMatrixIndex].row;
			}

			// 뒷 행렬 col 크면 앞 행렬은 다음 term 참조
			else if (termsArr[preMatrixIndex].col < trMatrix.termsArr[postMatrixIndex].col)
				preMatrixIndex++;

			// 앞 행렬의 col과 뒷 행렬의 col이 일치할 때만 곱셈 수행 & 각각 다음 term 참조
			else if (termsArr[preMatrixIndex].col == trMatrix.termsArr[postMatrixIndex].col)
			{
				rowSum = rowSum + termsArr[preMatrixIndex].val * trMatrix.termsArr[postMatrixIndex].val;
				preMatrixIndex++;
				postMatrixIndex++;
			}

			// 앞 행렬의 col 크면 뒷 행렬은 다음 term 참조
			else
				postMatrixIndex++;
		}

		//  rowPos 증가
		while (termsArr[preMatrixIndex].row == resultRowPos)
			preMatrixIndex++;
		
		resultRowPos = termsArr[preMatrixIndex].row;
		preMatrixRowExp = preMatrixIndex;					// 현재까지 확인한 앞 행렬 row를 기억
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
