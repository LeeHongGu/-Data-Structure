#include "Calculator.h"
#include "MyStack.h"
#include "CommonHeader.h"

// Constructor Destroyer
Calculator::Calculator()
{
	iToken = NULL;
	pToken = NULL;

	infixInput = "";
	result = 0;
	expPos = 0;
	iTokenCnt = 0;
	pTokenCnt = 0;
}
Calculator::~Calculator()
{
	if (iToken != NULL)
		delete[] iToken;
	if (pToken != NULL)
		delete[] pToken;
}

// Private Functions
int Calculator::inStackPriority(Token t)
{
	char type = t.getOp();
	switch (type)
	{
	case '!':
	case '~':	return 5;
	case '^':	return 4;
	case '*':
	case '/':
	case '%':	return 3;
	case '+':
	case '-':	return 2;
	case END_TOKEN:
	case '(':	return 1;
	}
}

int Calculator::inComingPriority(Token t)
{
	char type = t.getOp();
	switch (type)
	{
	case '(':	return 7;
	case '!':	return 6;					// isp(!,~) < icp(!,~)  ( to left combine )
	case '~':	return 6;
	case '^':	return 4;
	case '*':
	case '/':
	case '%':	return 3;
	case '+':
	case '-':	return 2;
	}
}

char Calculator::getNextToken(string expression)
{
	if (expression.at(expPos) == END_TOKEN)
	{
		expPos = 0;
		return END_TOKEN;
	}

	return expression.at(expPos++);
}

// Pulbic Functions
bool Calculator::setInfix(string input)
{
	if (input.find(END_TOKEN) != string::npos)					// check input have conditional charactors
		return false;
	else if (input.find(DIGIT) != string::npos)
		return false;
	else if (input.find_first_not_of(' ') == string::npos)		// check input is empty
		return false;
	else if (input.find_first_not_of('(') == string::npos)		// to prevent ()(), ()()(), ...
		return false;
	else if (input.find_first_not_of(')') == string::npos)
		return false;

	infixInput = input;
	return true;
}

bool Calculator::infixToToken()
{
	iToken = new Token[infixInput.length() + 1];
	infixInput = infixInput + END_TOKEN;	// append end of expression 

	bool wasNextBlank = false;				// to prevent 1 2 to 12
	int pairCnt = 0;						// pair of parethesis
	Token currToken;
	Token nextToken;

	currToken = getNextToken(infixInput);
	nextToken = ' ';
	while (currToken != END_TOKEN)
	{
		nextToken = getNextToken(infixInput);

		if (nextToken.checkToken() == BLANK)
			wasNextBlank = true;
		while (nextToken == ' ')							// trim spaces
			nextToken = getNextToken(infixInput);

		int type = currToken.checkToken();
		switch (type)
		{
		case OPERAND:
			iToken[iTokenCnt] = currToken;
			while (!wasNextBlank)								// successive number to one token
			{
				if (nextToken.checkToken() == OPERAND)
				{
					iToken[iTokenCnt] = nextToken + iToken[iTokenCnt] * 10;
					currToken = nextToken;
					nextToken = getNextToken(infixInput);
				}
				else
					break;
			}
			iTokenCnt++;
			break;

		case OPERATOR:
			if (nextToken.checkToken() == OPERATOR || nextToken == END_TOKEN || nextToken == ')')
				return false;
			else if (iTokenCnt != 0 && iToken[iTokenCnt - 1] == '(')
				return false;
			iToken[iTokenCnt++] = currToken;
			break;

		case NEGATIVE:
			if (nextToken.checkToken() == OPERATOR || nextToken == END_TOKEN)
				return false;
			else if (iTokenCnt == 0 || iToken[iTokenCnt - 1] == '~' || iToken[iTokenCnt - 1] == '-' || iToken[iTokenCnt - 1] == '!')
				iToken[iTokenCnt++] = '~';
			else if (iTokenCnt != 0 && iToken[iTokenCnt - 1].checkToken() == OPERATOR || iToken[iTokenCnt-1]=='(')
				iToken[iTokenCnt++] = '~';
			else
				iToken[iTokenCnt++] = currToken;
			break;

		case NOT:
			if (nextToken.checkToken() == OPERATOR || nextToken == END_TOKEN || nextToken==')')
				return false;
			else if (iTokenCnt != 0 && iToken[iTokenCnt - 1] == '('&&nextToken.checkToken() != OPERAND)
				return false;
			iToken[iTokenCnt++] = currToken;
			break;

		case PARENTHESIS:
			iToken[iTokenCnt++] = currToken;
			if (currToken == ')' && iToken[iTokenCnt - 2] == '(')										// prevent n()n
				return false;
			if (currToken == ')' && iToken[iTokenCnt - 2].checkToken() == OPERATOR)						// prvent n(op)n
				return false;
			else if (currToken == ')' &&  iToken[iTokenCnt - 2] == '~')
				return false;
			else if (currToken == ')' && (nextToken == '(' || nextToken.checkToken() == OPERAND))		// "(n)(n)"  to  "(n)*(n)"
			{
				iToken[iTokenCnt++] = '*';
				pairCnt--;
			}
			else if (currToken == '(' && iTokenCnt != 1 && iToken[iTokenCnt - 2].checkToken() == OPERAND)	// "n()n"  to  "n*()*n"
			{
				iToken[iTokenCnt - 1] = '*';
				iToken[iTokenCnt++] = currToken;
				pairCnt++;
			}
			else if (currToken == '(')
				pairCnt++;
			else
				pairCnt--;
			break;

		case BLANK: break;
		case ERROR: return false;
		}
		wasNextBlank = false;
		currToken = nextToken;
	}
	if (pairCnt != 0)
		return false;
	if (iToken[0] == ')')
		return false;

	return true;
}

bool Calculator::setPostfix()
{
	pToken = new Token[iTokenCnt+1];
	TokenStack stack;
	Token endOfExp;
	endOfExp = END_TOKEN;
	stack.push(endOfExp);

	for (int i = 0; i < iTokenCnt; i++)
	{
		Token t = iToken[i];

		if (t.checkToken() == OPERAND)
			pToken[pTokenCnt++] = t;
		else if (t == ')')
		{
			for (; stack.getTop() != '('; stack.pop())
				pToken[pTokenCnt++] = stack.getTop();
			stack.pop();
		}
		else					// token is operator
		{
			for (; inStackPriority(stack.getTop()) >= inComingPriority(t); stack.pop())
				pToken[pTokenCnt++] = stack.getTop();
			stack.push(t);
		}
	}
	for (; stack.getTop() != END_TOKEN; stack.pop())
		pToken[pTokenCnt++] = stack.getTop();

	return true;
}

void Calculator::printPostfix()
{
	cout << "--- 후위 계산식은 : ";
	for (int i = 0; i < pTokenCnt; i++)
		cout << pToken[i] << " ";
	cout << endl;
}

bool Calculator::setResult()
{
	TokenStack stack;
	Token temp;

	for (int i = 0; i < pTokenCnt; i++)
	{
		Token t = pToken[i];
		if (t.checkToken() == OPERAND)
			stack.push(t);
		else								// token is operator
		{
			int type = t.checkOpType();
		
			switch (type)
			{
			case ADD:
				temp = stack.getTop();
				stack.pop();
				if (stack.isEmpty())						// operand not remainning
				{
					cout << "[오류] 이해할 수 없는 수식\n";
					return false;
				}
				temp = stack.getTop() + temp;
				stack.pop();
				stack.push(temp);
				break;

			case SUBTRACT:
				temp = stack.getTop();
				stack.pop();
				if (stack.isEmpty())						// operand not remainning
				{
					cout << "[오류] 이해할 수 없는 수식\n";
					return false;
				}
				temp = stack.getTop() - temp;
				stack.pop();
				stack.push(temp);
				break;

			case MULTIPLY:
				temp = stack.getTop();
				stack.pop();
				if (stack.isEmpty())						// operand not remainning
				{
					cout << "[오류] 이해할 수 없는 수식\n";
					return false;
				}
				temp = stack.getTop() * temp;
				stack.pop();
				stack.push(temp);
				break;

			case DIVIDE:
				temp = stack.getTop();
				if (temp == 0)
				{
					cout << "[오류] 나누기의 두번째 연산자가 0인 경우가 발생\n";
					return false;
				}
				stack.pop();
				if (stack.isEmpty())						// operand not remainning
				{
					cout << "[오류] 이해할 수 없는 수식\n";
					return false;
				}
				temp = stack.getTop() / temp;
				stack.pop();
				stack.push(temp);
				break;

			case MODULO:
				temp = stack.getTop();
				if (temp == 0)
				{
					cout << "[오류] 나머지의 두번째 연산자가 0인 경우가 발생\n";
					return false;
				}
				stack.pop();
				if (stack.isEmpty())						// operand not remainning
				{
					cout << "[오류] 이해할 수 없는 수식\n";
					return false;
				}
				temp = stack.getTop() % temp;
				stack.pop();
				stack.push(temp);
				break;

			case POWER:
				temp = stack.getTop();
				stack.pop();
				if (stack.isEmpty())						// operand not remainning
				{
					cout << "[오류] 이해할 수 없는 수식\n";
					return false;
				}
				if (temp == 0 && stack.getTop()==0)
				{
					cout << "[오류] 0의 0제곱은 정의되지 않음\n";
					return false;
				}
				temp = stack.getTop() ^ temp;
				stack.pop();
				stack.push(temp);
				break;

			case UNARY_MINUS:
				temp = ~stack.getTop();
				stack.pop();
				stack.push(temp);
				break;

			case NOT:
				temp = !stack.getTop();
				stack.pop();
				stack.push(temp);
				break;

			}
		}		
	}

	temp = stack.getTop();
	stack.pop();

	if (!stack.isEmpty())						// operand remainning
	{
		cout << "[오류] 이해할 수 없는 수식\n";
		return false;
	}

	result = temp.getNum();
	return true;
}

void Calculator::clear()
{
	if (iToken != NULL)
		delete[] iToken;
	if (pToken != NULL)
		delete[] pToken;
	iToken = NULL;
	pToken = NULL;

	infixInput = "";
	result = 0;
	expPos = 0;
	iTokenCnt = 0;
	pTokenCnt = 0;
}