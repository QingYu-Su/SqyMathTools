#include <iostream>
#include <Windows.h>
#include "MathFunction.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
using namespace SqyMathLibrary;
using namespace std;

int main() {
	/*Calculator *clac = new Calculator;
	MathExpression a{ "3", "+", "10" };
	cout << clac -> Calculate(a);*/
	MathExpression a{ "3", "+", "x"};
	FunctionExpression b(a, 'y', 'x', -10, 10);
	/*FunctionTool k;
	cout << k.GetValue(b, 11) << endl;*/
	NormalFunction c(b);
	/*FunctionMap d = c->Calculate(-10, 10, 1);
	for (int i = 0; i < d.size(); i++) {
		cout << d[i].first << " " << d[i].second << endl;
	}*/
	return 0;
}