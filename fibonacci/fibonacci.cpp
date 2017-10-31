#include <iostream>
#include <time.h>
using namespace std;

int getNthFiboNum(int n);				//�ݺ��Լ�
int rgetNthFiboNum(int n);				//����Լ�

/*
�Է��� 10 �� ��� -> �ݺ� 4ms, ��� 2ms
�Է��� 20 �� ��� -> �ݺ� 4ms, ��� 2ms
�Է��� 30 �� ��� -> �ݺ� 4ms, ��� 42ms
�Է��� 40 �� ��� -> �ݺ� 4ms, ��� 4705ms
�Է��� 50 �� ��� -> �ݺ� 5ms, ��� 564013ms
=> �Է� ���� ���������� ����Լ��� ���۽ð��� �ݺ��Լ��� ���� �ް��ϰ� �����մϴ�.
�ݺ��Լ��� �Է°��� ���� ����޼������� �ܰ���� �����Կ� ����, 
����Լ��� ���ϱ޼������� �����ϱ� ������ �̷��� ������ �߻��Ͽ����ϴ�.
��, �Է°��� Ŀ������ ����Լ��� ȣ��󵵰� ���ϱ޼������� �þ�ԵǾ� ���۽ð��� ���ϵ� �� �Դϴ�.

50�� ���� �Ǻ���ġ ���� �������� ���� ����� ������ ����
=> �ڷ����� ���� �� �ִ� �ִ밪�� ������ ����� �����÷ο찡 �߻��Ͽ��� �����Դϴ�.
*/
int main()
{
	int num;
	clock_t start, end;
	cout << "n ��° �Ǻ���ġ �� ? :";
	cin >> num;

	start = clock();
	cout << num << "�� ° �Ǻ���ġ ���� :" << getNthFiboNum(num - 1) << " (�ݺ��Լ�. ";
	end = clock();
	cout << end - start << "ms)" << endl;

	start = clock();
	cout << num << "�� ° �Ǻ���ġ ���� :" << rgetNthFiboNum(num - 1) << " (����Լ�. ";
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