#include "./include/MathFunction.h"

namespace SqyMathLibrary {

	FunctionExpression::FunctionExpression(MathExpression expression, char iv, char dv, OPERAND maxDV = INF, OPERAND minDV = -INF)
		:m_Expression(expression), m_IV(iv), m_DV(dv), m_MaxDV(maxDV), m_MinDV(minDV)
	{}


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


}