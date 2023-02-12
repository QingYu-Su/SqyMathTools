#include "./include/MathFunction.h"

namespace SqyMathLibrary {

	FunctionExpression::FunctionExpression(MathExpression &expression, char iv, char dv, OPERAND maxDV, OPERAND minDV)
		:m_Expression(expression), m_IV(iv), m_DV(dv), m_MaxDV(maxDV), m_MinDV(minDV)
	{}

	OPERAND FunctionExpression::Calculate(OPERAND value) {
		//超过定义域区间返回INF，默认为左闭右闭区间，若区间定义方式不同，请在外部设置调用
		if (value > this->m_MaxDV || value < this->m_MinDV) return INF;

		MathExpression expression = this->m_Expression;

		for (int i = 0; i < expression.size(); i++) {
			if (expression[i].size() == 1 && expression[i][0] == this->m_DV) {
				expression[i] = std::to_string(value);
			}
		}
		
		Calculator calc;
		OPERAND res = calc.Calculate(expression);
		if (calc.IsSuccess() == false) return INF;
		return res;
	}


	MathFunction::MathFunction(FunctionType type, Function& function, size_t accuracy)
		:m_Type(type), m_Function(function), m_Accuracy(accuracy)
	{}

	FunctionType MathFunction::GetType() {
		return this->m_Type;
	}

	Function MathFunction::GetFunction() {
		return this->m_Function;
	}

	size_t MathFunction::GetAccuracy() {
		return this->m_Accuracy;
	}

	void MathFunction::SetFunction(Function &function) {
		this->m_Function = function;
	}
	void MathFunction::SetAccuracy(size_t accuracy) {
		this->m_Accuracy = accuracy;
	}

	NormalFunction::NormalFunction(Function& function, size_t accuracy)
		:MathFunction(Normal, function, accuracy)
	{}

	OPERAND NormalFunction::GetY(OPERAND value) {
		OPERAND res = INF;
		for (int i = 0; i < this->m_Function.size(); i++) {
			if (this->m_Function[i].m_DV == 'x' && this->m_Function[i].m_IV == 'y') {
				res = this->m_Function[i].Calculate(value);
				if (res != INF) break;
			}
		}
		return res;
	}
}