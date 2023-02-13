#include "./include/MathFunction.h"

namespace SqyMathLibrary {

	FunctionExpression::FunctionExpression(MathExpression& expression, char iv, char dv, OPERAND left, OPERAND right)
		:m_Expression(expression), m_IV(iv), m_DV(dv)
	{
		if (right > INF) right = INF;
		if (left < -INF) left = -INF;
		this->m_Left = left;
		this->m_Right = right;
	}


	MathFunction::MathFunction(FunctionType type, Function& function)
		:m_Type(type), m_Function(function)
	{
		this->m_MaxX = -INF;
		this->m_MaxY = -INF;
		this->m_MinX = INF;
		this->m_MinY = INF;
		this->m_Error = "";
	}

	FunctionType MathFunction::GetType() {
		return this->m_Type;
	}

	Function MathFunction::GetFunction() {
		return this->m_Function;
	}

	void MathFunction::SetFunction(Function &function) {
		this->m_Function = function;
	}

	std::string MathFunction::GetError() {
		return this->m_Error;
	}

	void MathFunction::TranslateExpression(MathExpression& me, char c, OPERAND value) {
		for (int i = 0; i < me.size(); i++) {
			if (me[i].size() == 1 && me[i][0] == c) {
				me[i] = std::to_string(value);
			}
		}
	}

	OPERAND MathFunction::GetValue(OPERAND parameter, int index) {
		MathExpression me = this->m_Function[index].m_Expression;
		char dv = this->m_Function[index].m_DV;

		TranslateExpression(me, dv, parameter);

		OPERAND res = this->m_Calc.Calculate(me);

		if (this->m_Calc.IsSuccess() == false) {
			std::string error = this->m_Calc.GetError();
			if (error == CALC_ERROR_TAN || error == CALC_ERROR_DIV0) return INF;
			this->m_Error = error;
			return INV;
		}
		return res;
	}

	void MathFunction::Pretreat() {
		
	}

	NormalFunction::NormalFunction(Function& function)
		:MathFunction(Normal, function)
	{}

	bool NormalFunction::IsValid() {
		for (int i = 0; i < m_Function.size(); i++) {
			FunctionExpression& fe = this->m_Function[i];

			if (fe.m_DV != 'x') {
				this->m_Error = FUNC_ERROR_DV; return false;
			}

			if (fe.m_IV != 'y') {
				this->m_Error = FUNC_ERROR_IV; return false;
			}
		}
		return true;
	}

	bool NormalFunction::Calculate(OPERAND minDV, OPERAND maxDV, size_t precision) {
		m_FPMap.clear();
		
		if (this->IsValid() == false) return false;

		OPERAND unit = (maxDV - minDV) / precision;
		int index = 0;
		OPERAND x = minDV;

		while (x <= maxDV && index < m_Function.size() ) {

			if (x < this->m_Function[index].m_Left || x > this->m_Function[index].m_Right) {
				index++;
				continue;
			}

			OPERAND y = this->GetValue(x, index);
			if (y == INV) return false;

			FunctionPoint fp;
			fp.first = x;
			fp.second = y;
			this->m_FPMap.push_back(fp);

			x += unit;
		}

		return true;
	}

	PolarFunction::PolarFunction(Function& function)
		:MathFunction(Polar, function)
	{}

	bool PolarFunction::IsValid() {
		for (int i = 0; i < m_Function.size(); i++) {
			FunctionExpression& fe = this->m_Function[i];

			if (fe.m_DV != 'a') {
				this->m_Error = FUNC_ERROR_DV; return false;
			}

			if (fe.m_IV != 'r') {
				this->m_Error = FUNC_ERROR_IV; return false;
			}
		}
		return true;
	}

	bool PolarFunction::Calculate(OPERAND minDV, OPERAND maxDV, size_t precision) {
		m_FPMap.clear();

		
		if (this->IsValid() == false) return false;
		OPERAND unit = (maxDV - minDV) / precision;
		int index = 0;
		OPERAND a = minDV;

		while (a <= maxDV && index < m_Function.size()) {

			if (a < this->m_Function[index].m_Left || a > this->m_Function[index].m_Right) {
				index++;
				continue;
			}

			OPERAND r = this->GetValue(a, index);
			if (r == INV) return false;

			OPERAND x = r * cos(a);
			OPERAND y = r * sin(a);

			FunctionPoint fp;
			fp.first = x;
			fp.second = y;
			this->m_FPMap.push_back(fp);

			x += unit;
		}

		return true;
	}

	ParaFunction::ParaFunction(Function& function)
		:MathFunction(Parametric, function)
	{}

	bool ParaFunction::IsValid() {
		for (int i = 0; i < m_Function.size(); i++) {
			FunctionExpression& fe = this->m_Function[i];

			if (fe.m_DV != 't') {
				this->m_Error = FUNC_ERROR_DV; return false;
			}

			if (fe.m_IV != 'x' || fe.m_IV != 'y') {
				this->m_Error = FUNC_ERROR_IV; return false;
			}
		}
		return true;
	}

	void ParaFunction::Pretreat() {
		
	}


	bool ParaFunction::Calculate(OPERAND minDV, OPERAND maxDV, size_t precision) {
		m_FPMap.clear();

		if (this->IsValid() == false) return false;
		OPERAND unit = (maxDV - minDV) / precision;
		int index = 0;
		OPERAND t = minDV;

		while (t <= maxDV && index < m_Function.size()) {

			if (t < this->m_Function[index].m_Left || t > this->m_Function[index].m_Right) {
				index++;
				continue;
			}

			

			x += unit;
		}

		return true;
	}
}