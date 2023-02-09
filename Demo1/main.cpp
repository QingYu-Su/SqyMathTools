#include "MathOperator.h"
#include <iostream>
#include "Calculator.h"
using namespace SqyMathLibrary;
using namespace std;

int main() {
	Calculator calc;
	vector<string> s{ "3", "+", "(", "7", "*", "(", "2","^", "2", ")", ")" };
	cout << calc.Calculate(s) << endl;
	if (calc.IsSuccess() == false) cout << calc.GetError() << endl;
	return 0;
}