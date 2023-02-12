#include "./include/MathFunction.h"

namespace SqyMathLibrary {

	FunctionExpression::FunctionExpression(MathExpression &expression, char iv, char dv, OPERAND maxDV, OPERAND minDV)
		:m_Expression(expression), m_IV(iv), m_DV(dv)
	{
		if (maxDV > INF) maxDV= INF;
		if (minDV < -INF) minDV = INF;
		this->m_MaxDV = maxDV;
		this->m_MinDV = minDV;
	}

	OPERAND FunctionExpression::Calculate(OPERAND value) {

		MathExpression expression = this->m_Expression;

		for (int i = 0; i < expression.size(); i++) {
			if (expression[i].size() == 1 && expression[i][0] == this->m_DV) {
				expression[i] = std::to_string(value);
			}
		}
		
		OPERAND res = m_Calc.Calculate(expression);
		if (m_Calc.IsSuccess() == false) {
			if (m_Calc.GetError() == CALC_ERROR_TAN || m_Calc.GetError() == CALC_ERROR_DIV0) res = INF;
			else res = IVE;
		}
		return res;
	}

	std::string FunctionExpression::GetError() {
		return this->GetError();
	}

	bool FunctionExpression::IsValid() {
		OPERAND mid = (this->m_MaxDV + this->m_MinDV) / 2;
		if (this->Calculate(mid) == IVE) return false;
		return true;
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
			FunctionExpression &fe = this->m_Function[i];
			if (fe.m_DV == 'x' && fe.m_IV == 'y' && value <= fe.m_MaxDV && value >= fe.m_MinDV ) {
				res = fe.Calculate(value);
				break;
			}
		}

		return res;
	}

	FPSet NormalFunction::Calculate(OPERAND xLeft, OPERAND xRight) {
		FPSet res;
		FunctionPoint fp;
		OPERAND unit = (xLeft - xRight) / this->m_Accuracy;
		for (OPERAND x = xLeft; x <= xRight; x += unit) {
			
			OPERAND y = this->GetY(x);
			
			if (y == IVE) {
				res.clear(); break;
			}
			
			fp.first = x;
			fp.second = y;
			res.push_back(fp);
		
		}
		return res;
	}
}