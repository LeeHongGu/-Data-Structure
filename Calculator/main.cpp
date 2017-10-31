#include "Calculator.h"

int main()
{
	string input;
	Calculator calc;
	
	while (input != "quit")
	{
		cout << "\n������ �Է��ϼ���(����� quit) : ";
		getline(cin, input);
		if (input == "quit")
		{
			cout << "**** �����մϴ� ****\n";
			break;
		}

		if (!calc.setInfix(input) || !calc.infixToToken() || !calc.setPostfix())
		{
			cout << "[����] ������ �� ���� ����\n";
			calc.clear();
			continue;
		}

		calc.printPostfix();
		if (calc.setResult())									// calculate & print result
			cout << "---- ����� " << calc.getResult() << endl;
		
		calc.clear();
	}
	
	return 0;
}