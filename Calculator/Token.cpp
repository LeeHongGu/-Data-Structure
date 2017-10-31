#include "Token.h"
#include "CommonHeader.h"

Token::Token()
{
	num = 0;
	op = NULL;
}
int Token::checkToken()
{
	switch (op)
	{
	case DIGIT:	return OPERAND;
	case '+':
	case '*':
	case '/':
	case '%':
	case '^':	return OPERATOR;
	case '-':	return NEGATIVE;
	case '!':	return NOT;
	case '(':
	case ')':	return PARENTHESIS;
	case ' ':	return BLANK;
	case END_TOKEN:		return END;
	default:	return ERROR;
	}

	return 0;
}
int Token::checkOpType()
{
	switch (op)
	{
	case '+': return ADD;
	case '-': return SUBTRACT;
	case '*': return MULTIPLY;
	case '/': return DIVIDE;
	case '%': return MODULO;
	case '^': return POWER;
	case '~': return UNARY_MINUS;
	case '!': return NOT;
	}
}

// Calculate
int Token::operator +(int num)
{
	return (int)((this->num) + num);
}
int Token::operator *(int num)
{
	return (int)((this->num) * num);
}
int Token::operator !()
{
	if (this->getNum() != 0)
		return 0;
	else
		return 1;
}
int Token::operator ~()
{
	return -(this->getNum());
}
int Token::operator +(Token t)
{
	return this->getNum() + t.getNum();
}
int Token::operator -(Token t)
{
	return this->getNum() - t.getNum();
}
int Token::operator *(Token t)
{
	return this->getNum() * t.getNum();
}
int Token::operator /(Token t)
{
	return this->getNum() / t.getNum();
}
int Token::operator %(Token t)
{
	return this->getNum() % t.getNum();
}
int Token::operator ^(Token t)
{
	if (this->getNum() == -1)							// -1^-n =  -1 or 1
		return t.getNum() % 2 ? -1 : 1;
	else if (t.getNum() == 0)							// n^0 = 0
		return 1;
	else if (this->getNum() == 1)						// 1^-n = 1
		return this->getNum();
	else if (t.getNum() < 0)							// operand must be integer
		return 0;

	int temp = this->getNum();
	for (int i = 0; i < t.getNum()-1; i++)
	{
		*this = this->getNum()*temp;
	}

	return this->getNum();
}

// Compare
bool Token::operator ==(int n)
{
	if (num == n)
		return true;

	return false;
}
bool Token::operator ==(char c)
{
	if (op == c)
		return true;

	return false;
}
bool Token::operator ==(Token t)
{
	if ((op == DIGIT) && (num == t.num))
		return true;
	else if ((op != DIGIT) && (op == t.op))
		return true;

	return false;
}
bool Token::operator !=(char c)
{
	if (op == c)
		return false;

	return true;
}
bool Token::operator !=(Token t)
{
	if ((op == DIGIT) && (num == t.num))
		return false;
	else if ((op != DIGIT) && (op == t.op))
		return false;

	return true;
}

// Assignment
Token& Token::operator = (int num)
{
	this->num = num;
	this->op = DIGIT;

	return *this;
}
Token& Token::operator = (char op)
{
	if ('0' <= op && op <= '9')
	{
		this->num = op - '0';
		this->op = DIGIT;
	}
	else
	{
		this->num = 0;
		this->op = op;
	}

	return *this;
}
Token& Token::operator = (Token& t)
{
	if (t.checkToken() == OPERAND)
		*this = t.getNum();
	else
		*this = t.getOp();

	return *this;
}

// Output
ostream& operator << (ostream& os, Token& t)
{
	if (t.checkToken() == OPERAND)
		os << t.getNum();
	else
		os << t.getOp();

	return os;
}