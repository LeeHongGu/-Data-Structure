#include "Calculator.h"

int main()
{
	string input;
	Calculator calc;
	
	while (input != "quit")
	{
		cout << "\n계산식을 입력하세요(종료는 quit) : ";
		getline(cin, input);
		if (input == "quit")
		{
			cout << "**** 종료합니다 ****\n";
			break;
		}

		if (!calc.setInfix(input) || !calc.infixToToken() || !calc.setPostfix())
		{
			cout << "[오류] 이해할 수 없는 수식\n";
			calc.clear();
			continue;
		}

		calc.printPostfix();
		if (calc.setResult())									// calculate & print result
			cout << "---- 결과는 " << calc.getResult() << endl;
		
		calc.clear();
	}
	
	return 0;
}