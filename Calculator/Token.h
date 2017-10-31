#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "MyStack.h"
#include "CommonHeader.h"

enum TOKEN_TYPE { OPERAND, OPERATOR, NEGATIVE, PARENTHESIS, BLANK, END, ERROR };
enum OP_TYPE { ADD, SUBTRACT, MULTIPLY, DIVIDE, MODULO, POWER, UNARY_MINUS, NOT};
const char END_TOKEN = '#';					// # means end of expression
const char DIGIT = '@';						// @ means this Token is Digit Token

class Token
{
private:
	int num;
	char op;
public:	
	Token();

	int getNum() { return (int)num; }
	char getOp() { return op; }
	int checkToken(); 
	int checkOpType();

	int operator +(int num);
	int operator *(int num);
	int operator !();
	int operator ~();
	int operator +(Token t);
	int operator -(Token t);
	int operator *(Token t);
	int operator /(Token t);
	int operator %(Token t);
	int operator ^(Token t);

	bool operator ==(int n);
	bool operator ==(char c);
	bool operator ==(Token t);
	bool operator !=(char c);
	bool operator !=(Token t);

	Token& operator = (int num);
	Token& operator = (char op);
	Token& operator = (Token& t);
};

class TokenStack : public MyStack<Token>
{
public :
	Token getTop()								// overloading stack's getTop()
	{
		Token result;
		if (isEmpty())
			return result;

		if (stack[top].checkToken() == OPERAND)
			result = stack[top].getNum();
		else
			result = stack[top].getOp();

		return result;
	}
};

ostream& operator << (ostream& os, Token& t);

#endif