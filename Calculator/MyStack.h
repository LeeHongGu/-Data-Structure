#ifndef __MY_STACK_H__
#define __MY_STACK_H__

#include "CommonHeader.h"

template <typename T>
class MyStack 
{
protected:
	T* stack;
	int capacity;
	int top;

	void doubleCapacity();

public:
	MyStack();
	~MyStack();

	void push(T& item);
	T getTop();
	void pop();
	bool isEmpty();
};

template <typename T>
MyStack<T>::MyStack() 
{
	capacity = 10;
	stack = new T[capacity];
	top = -1;
}

template <typename T>
MyStack<T>::~MyStack()
{
	if(stack != NULL)
		delete[] stack;
}

template <typename T>
void MyStack<T>::doubleCapacity()
{
	T* temp = new T[capacity * 2];

	for (int i = 0; i < top; i++)
		temp[i] = stack[i];

	delete[] stack;
	stack = temp;
}

template <typename T>
void MyStack<T>::push(T& item)
{
	if (top+1 == capacity)
		doubleCapacity();

	stack[++top] = item;
}

template <typename T>
void MyStack<T>::pop()
{
	if (top == -1)
		return;
	else
		top--;
}

template <typename T>
T MyStack<T>::getTop()
{
	if (isEmpty())
		return NULL;

	return stack[top];
}

template <typename T>
bool MyStack<T>::isEmpty()
{
	if (top == -1)
		return true;

	return false;
}

#endif