#include <iostream>
#include "Calculator.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
using namespace SqyMathLibrary;
using namespace std;

int main() {
	Calculator calc;
	vector<string> s{ "3", "+", "(", "7", "*", "(", "2","^", "2", ")", ")" };
	cout << calc.Calculate(s) << endl;
	if (calc.IsSuccess() == false) cout << calc.GetError() << endl;
	return 0;
}