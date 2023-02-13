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


	bool MathFunction::Calculate(OPERAND left, OPERAND right, size_t precision) {
		if (this->IsValid() == false) return false;
		
		this->PreProcess();

		this->m_Map.clear();

		OPERAND unit = (right - left) / precision;
		
		for (OPERAND parameter = left; parameter <= right; parameter += unit) {
			
			OPERAND x = this->GetX(parameter);
			if (x == INV) return false;

			OPERAND y = this->GetY(parameter);
			if (y == INV) return false;

			this->m_MaxX = std::max(this->m_MaxX, x);
			this->m_MinX = std::min(this->m_MinX, x);
			this->m_MaxY = std::max(this->m_MaxY, y);
			this->m_MinY = std::min(this->m_MinY, y);

			FunctionPoint fp;
			fp.first = x;
			fp.second = y;

			m_Map.push_back(fp);
		}

		this->PostProcess();

		return true;
	}

	bool NormalFunction::IsValid() {
		if (this->m_Expression.m_DV != 'x') {
			this->SetError(FUNC_ERROR_DV);
			return false;
		}

		if (this->m_Expression.m_IV != 'y') {
			this->SetError(FUNC_ERROR_IV);
			return false;
		}

	}

	OPERAND NormalFunction::GetX(OPERAND parameter) {
		return parameter;
	}

	OPERAND NormalFunction::GetY(OPERAND parameter) {
		OPERAND res = this->m_Tool.GetValue(this->m_Expression, parameter);
		if (this->m_Tool.IsSuccess() == false) {
			this->SetError(this->m_Tool.GetError());
			return INV;
		}
		return res;
	}

	bool PolarFunction::IsValid() {
		if (this->m_Expression.m_DV != 'a') {
			this->SetError(FUNC_ERROR_DV);
			return false;
		}

		if (this->m_Expression.m_IV != 'r') {
			this->SetError(FUNC_ERROR_IV);
			return false;
		}

	}

	OPERAND PolarFunction::GetR(OPERAND parameter) {
		OPERAND res = this->m_Tool.GetValue(this->m_Expression, parameter);
		if (this->m_Tool.IsSuccess() == false) {
			this->SetError(this->m_Tool.GetError());
			return INV;
		}
		return res;
	}

	OPERAND PolarFunction::GetX(OPERAND parameter) {
		OPERAND r = this->GetR(parameter);
		if (r == INV) return false;
		return r * cos(parameter);
	}

	OPERAND PolarFunction::GetY(OPERAND parameter) {
		OPERAND r = this->GetR(parameter);
		if (r == INV) return false;
		return r * sin(parameter);
	}

	bool TwoFunction::IsValid() {
		if (this->m_ExpressionX.m_DV != 't' || this->m_ExpressionY.m_DV != 't' ) {
			this->SetError(FUNC_ERROR_DV);
			return false;
		}

		if (this->m_ExpressionX.m_IV != 'x' || this->m_ExpressionY.m_IV != 'y' ) {
			this->SetError(FUNC_ERROR_IV);
			return false;
		}

	}

	OPERAND TwoFunction::GetX(OPERAND parameter) {
		OPERAND res = this->m_Tool.GetValue(this->m_ExpressionX, parameter);
		if (this->m_Tool.IsSuccess() == false) {
			this->SetError(this->m_Tool.GetError());
			return INV;
		}
		return res;
	}

	OPERAND TwoFunction::GetY(OPERAND parameter) {
		OPERAND res = this->m_Tool.GetValue(this->m_ExpressionY, parameter);
		if (this->m_Tool.IsSuccess() == false) {
			this->SetError(this->m_Tool.GetError());
			return INV;
		}
		return res;
	}
}