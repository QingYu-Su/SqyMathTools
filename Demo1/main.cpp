#include "MathOperator.h"
#include <iostream>
#include "MathOperatorMap.h"
using namespace SqyMathLibrary;
using namespace std;

class AAA :public MathOperator {
public:
	AAA() : MathOperator("aaa", 1, 5) {}
	OPERAND Operate(const OPERAND a, const OPERAND b) {
		return a + b * 2;
	}
	~AAA() {
		cout << "aaa";
	}
};

int main() {
	MathOperator* p = GET_MATH_OPERATOR("+");
	DESTROY_MATH_OPERATOR("*");
	p = GET_MATH_OPERATOR("*");
	if (p == NULL) {
		cout << "not" << endl;
	}
	REGISTER_MATH_OPERATOR("*", AAA);
	p = GET_MATH_OPERATOR("*");
	cout << p->Operate(10, 20);
	return 0;
}