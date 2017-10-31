#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "Token.h"

class Calculator
{
private:
	int result;
	int expPos;					// expreession position index

	string infixInput;			// user input
	Token* iToken;				// infix tokens
	Token* pToken;				// postfix tokens
	int iTokenCnt;
	int pTokenCnt; 

	char getNextToken(string expression);
	int inStackPriority(Token t);
	int inComingPriority(Token t);
public:
	Calculator();
	~Calculator();

	bool setInfix(string input);
	bool infixToToken();
	bool setPostfix();
	void printPostfix();
	bool setResult();
	int getResult() { return result; }
	void clear();
};

#endif