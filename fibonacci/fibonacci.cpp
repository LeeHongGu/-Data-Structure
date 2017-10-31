#include <iostream>
#include <time.h>
using namespace std;

int getNthFiboNum(int n);				//반복함수
int rgetNthFiboNum(int n);				//재귀함수

/*
입력이 10 인 경우 -> 반복 4ms, 재귀 2ms
입력이 20 인 경우 -> 반복 4ms, 재귀 2ms
입력이 30 인 경우 -> 반복 4ms, 재귀 42ms
입력이 40 인 경우 -> 반복 4ms, 재귀 4705ms
입력이 50 인 경우 -> 반복 5ms, 재귀 564013ms
=> 입력 값의 증가에따라 재귀함수의 동작시간은 반복함수에 비해 급격하게 증가합니다.
반복함수는 입력값에 따라 산술급수적으로 단계수가 증가함에 반해, 
재귀함수는 기하급수적으로 증가하기 때문에 이러한 현상이 발생하였습니다.
즉, 입력값이 커질수록 재귀함수의 호출빈도가 기하급수적으로 늘어나게되어 동작시간이 저하된 것 입니다.

50에 대한 피보나치 값이 예상하지 못한 결과가 나오는 이유
=> 자료형이 담을 수 있는 최대값의 범위를 벗어나는 오버플로우가 발생하였기 때문입니다.
*/
int main()
{
	int num;
	clock_t start, end;
	cout << "n 번째 피보나치 수 ? :";
	cin >> num;

	start = clock();
	cout << num << "번 째 피보나치 수는 :" << getNthFiboNum(num - 1) << " (반복함수. ";
	end = clock();
	cout << end - start << "ms)" << endl;

	start = clock();
	cout << num << "번 째 피보나치 수는 :" << rgetNthFiboNum(num - 1) << " (재귀함수. ";
	end = clock();
	cout << end - start << "ms)" << endl;

	return 0;
}

int getNthFiboNum(int n)
{
	int fib, fib1 = 0, fib2 = 1;

	if (n<2)
		return n;
	else
		for (int i = 2; i <= n; i++)
		{
			fib = fib1 + fib2;
			fib1 = fib2;
			fib2 = fib;
		}

	return fib;
}
int rgetNthFiboNum(int n)
{
	if (n<2)
		return n;
	else
		return rgetNthFiboNum(n - 1) + rgetNthFiboNum(n - 2);
}