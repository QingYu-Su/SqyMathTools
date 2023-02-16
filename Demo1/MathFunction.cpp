#include "./include/MathFunction.h"

namespace SqyMathLibrary {

	MathFunction::MathFunction(FunctionType type) {
		this->m_Type = type;
		this->m_MinX = INF;
		this->m_MaxX = -INF;
		this->m_MinY = INF;
		this->m_MaxY = -INF;
		this->m_Error = "";
	}

	FunctionMap MathFunction::Calculate(OPERAND left, OPERAND right, size_t precision) {
		FunctionMap res;

		if (this->IsValid() == false) return res;  //函数无效，直接返回
		
		this->PreProcess();  //预处理

		OPERAND unit = (right - left) / precision;  //函数计算单元
		
		for (OPERAND parameter = left; parameter <= right; parameter += unit) {
			
			OPERAND x = this->GetX(parameter);  //获取x值
			if (x == INV) {
				res.clear();  
				return res;  //x值无效，直接返回
			} 

			OPERAND y = this->GetY(parameter);  //获取y值
			if (y == INV) {
				res.clear();  return res; //y值无效，直接返回
			}
			 
			//更新X和Y的极值
			this->m_MaxX = std::max(this->m_MaxX, x);
			this->m_MinX = std::min(this->m_MinX, x);
			this->m_MaxY = std::max(this->m_MaxY, y);
			this->m_MinY = std::min(this->m_MinY, y);

			//添加函数点
			FunctionPoint fp;
			fp.first = x;
			fp.second = y;
			res.push_back(fp);
		}

		this->PostProcess();  //后处理

		return res;
	}

	std::string MathFunction::GetError() {
		return this->m_Error;
	}

	bool MathFunction::IsSuccess() {
		return this->m_Success;
	}

	void MathFunction::SetResult(bool res, std::string reason) {
		this->m_Success = res;
		this->m_Error = reason;
	}

	NormalFunction::NormalFunction(FunctionExpression &expression)
		:MathFunction(Normal), m_Expression(expression)
	{}

	bool NormalFunction::IsValid() {
		if (this->m_Expression.m_DV != 'x') {  //自变量必须为'x'
			this->SetResult(false, FUNC_ERROR_DV);
			return false;
		}

		if (this->m_Expression.m_IV != 'y') {  //因变量必须为'y'
			this->SetResult(false, FUNC_ERROR_DV);
			return false;
		}

	}

	OPERAND NormalFunction::GetX(OPERAND parameter) {
		return parameter;  //直接返回x值
	}

	OPERAND NormalFunction::GetY(OPERAND parameter) {
		OPERAND y = this->m_Tool.GetValue(this->m_Expression, parameter); //计算y值

		if (this->m_Tool.IsSuccess() == false) {  //计算是否出错
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //超过定义域不返回错误，直接返回INF，表示该点在y轴上无定义
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //其他错误返回INV
				return INV;
			}
		}
		return y;
	}

	PolarFunction::PolarFunction(FunctionExpression& expression)
		:MathFunction(Polar), m_Expression(expression)
	{}

	bool PolarFunction::IsValid() {
		if (this->m_Expression.m_DV != 'a') {  //自变量必须为'a'
			this->SetResult(false, FUNC_ERROR_DV);
			return false;
		}

		if (this->m_Expression.m_IV != 'r') {  //因变量必须为'r'
			this->SetResult(false, FUNC_ERROR_IV);
			return false;
		}

	}

	OPERAND PolarFunction::GetR(OPERAND parameter) {
		OPERAND r = this->m_Tool.GetValue(this->m_Expression, parameter);  //计算r值

		if (this->m_Tool.IsSuccess() == false) {  //计算是否出错
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //超过定义域不返回错误，直接返回INF
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //其他错误返回INV
				return INV;
			}
		}
		return r;
	}

	OPERAND PolarFunction::GetX(OPERAND parameter) {
		OPERAND r = this->GetR(parameter);  //获取角度对应的r值
		if (r == INV) return INV;  //r值无效则返回INV
		return r * cos(parameter); 
	}

	OPERAND PolarFunction::GetY(OPERAND parameter) {
		OPERAND r = this->GetR(parameter);  //获取角度对应的r值
		if (r == INV) return INV;  //r值无效则返回INV
		return r * sin(parameter);
	}

	TwoFunction::TwoFunction(FunctionExpression& expressionX, FunctionExpression& expressionY)
		:MathFunction(Two), m_ExpressionX(expressionX), m_ExpressionY(expressionY)
	{}

	bool TwoFunction::IsValid() {
		if (this->m_ExpressionX.m_DV != 't' || this->m_ExpressionY.m_DV != 't' ) {
			this->SetResult(false, FUNC_ERROR_DV);  //自变量必须为't'
			return false;
		}

		if (this->m_ExpressionX.m_IV != 'x' || this->m_ExpressionY.m_IV != 'y' ) {
			this->SetResult(false, FUNC_ERROR_IV);  //因变量必须为'x'与'y'
			return false;
		}

	}

	OPERAND TwoFunction::GetX(OPERAND parameter) {
		OPERAND x = this->m_Tool.GetValue(this->m_ExpressionX, parameter);  //获取x值
		if (this->m_Tool.IsSuccess() == false) {  //计算是否出错
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //超过定义域不返回错误，直接返回INF
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //其他错误返回INV
				return INV;
			}
		}
		return x;
	}

	OPERAND TwoFunction::GetY(OPERAND parameter) {
		OPERAND y = this->m_Tool.GetValue(this->m_ExpressionY, parameter);  //获取x值
		if (this->m_Tool.IsSuccess() == false) {  //计算是否出错
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //超过定义域不返回错误，直接返回INF
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //其他错误返回INV
				return INV;
			}
		}
		return y;
	}
}