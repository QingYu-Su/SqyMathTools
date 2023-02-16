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

		if (this->IsValid() == false) return res;  //������Ч��ֱ�ӷ���
		
		this->PreProcess();  //Ԥ����

		OPERAND unit = (right - left) / precision;  //�������㵥Ԫ
		
		for (OPERAND parameter = left; parameter <= right; parameter += unit) {
			
			OPERAND x = this->GetX(parameter);  //��ȡxֵ
			if (x == INV) {
				res.clear();  
				return res;  //xֵ��Ч��ֱ�ӷ���
			} 

			OPERAND y = this->GetY(parameter);  //��ȡyֵ
			if (y == INV) {
				res.clear();  return res; //yֵ��Ч��ֱ�ӷ���
			}
			 
			//����X��Y�ļ�ֵ
			this->m_MaxX = std::max(this->m_MaxX, x);
			this->m_MinX = std::min(this->m_MinX, x);
			this->m_MaxY = std::max(this->m_MaxY, y);
			this->m_MinY = std::min(this->m_MinY, y);

			//��Ӻ�����
			FunctionPoint fp;
			fp.first = x;
			fp.second = y;
			res.push_back(fp);
		}

		this->PostProcess();  //����

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
		if (this->m_Expression.m_DV != 'x') {  //�Ա�������Ϊ'x'
			this->SetResult(false, FUNC_ERROR_DV);
			return false;
		}

		if (this->m_Expression.m_IV != 'y') {  //���������Ϊ'y'
			this->SetResult(false, FUNC_ERROR_DV);
			return false;
		}

	}

	OPERAND NormalFunction::GetX(OPERAND parameter) {
		return parameter;  //ֱ�ӷ���xֵ
	}

	OPERAND NormalFunction::GetY(OPERAND parameter) {
		OPERAND y = this->m_Tool.GetValue(this->m_Expression, parameter); //����yֵ

		if (this->m_Tool.IsSuccess() == false) {  //�����Ƿ����
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //���������򲻷��ش���ֱ�ӷ���INF����ʾ�õ���y�����޶���
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //�������󷵻�INV
				return INV;
			}
		}
		return y;
	}

	PolarFunction::PolarFunction(FunctionExpression& expression)
		:MathFunction(Polar), m_Expression(expression)
	{}

	bool PolarFunction::IsValid() {
		if (this->m_Expression.m_DV != 'a') {  //�Ա�������Ϊ'a'
			this->SetResult(false, FUNC_ERROR_DV);
			return false;
		}

		if (this->m_Expression.m_IV != 'r') {  //���������Ϊ'r'
			this->SetResult(false, FUNC_ERROR_IV);
			return false;
		}

	}

	OPERAND PolarFunction::GetR(OPERAND parameter) {
		OPERAND r = this->m_Tool.GetValue(this->m_Expression, parameter);  //����rֵ

		if (this->m_Tool.IsSuccess() == false) {  //�����Ƿ����
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //���������򲻷��ش���ֱ�ӷ���INF
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //�������󷵻�INV
				return INV;
			}
		}
		return r;
	}

	OPERAND PolarFunction::GetX(OPERAND parameter) {
		OPERAND r = this->GetR(parameter);  //��ȡ�Ƕȶ�Ӧ��rֵ
		if (r == INV) return INV;  //rֵ��Ч�򷵻�INV
		return r * cos(parameter); 
	}

	OPERAND PolarFunction::GetY(OPERAND parameter) {
		OPERAND r = this->GetR(parameter);  //��ȡ�Ƕȶ�Ӧ��rֵ
		if (r == INV) return INV;  //rֵ��Ч�򷵻�INV
		return r * sin(parameter);
	}

	TwoFunction::TwoFunction(FunctionExpression& expressionX, FunctionExpression& expressionY)
		:MathFunction(Two), m_ExpressionX(expressionX), m_ExpressionY(expressionY)
	{}

	bool TwoFunction::IsValid() {
		if (this->m_ExpressionX.m_DV != 't' || this->m_ExpressionY.m_DV != 't' ) {
			this->SetResult(false, FUNC_ERROR_DV);  //�Ա�������Ϊ't'
			return false;
		}

		if (this->m_ExpressionX.m_IV != 'x' || this->m_ExpressionY.m_IV != 'y' ) {
			this->SetResult(false, FUNC_ERROR_IV);  //���������Ϊ'x'��'y'
			return false;
		}

	}

	OPERAND TwoFunction::GetX(OPERAND parameter) {
		OPERAND x = this->m_Tool.GetValue(this->m_ExpressionX, parameter);  //��ȡxֵ
		if (this->m_Tool.IsSuccess() == false) {  //�����Ƿ����
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //���������򲻷��ش���ֱ�ӷ���INF
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //�������󷵻�INV
				return INV;
			}
		}
		return x;
	}

	OPERAND TwoFunction::GetY(OPERAND parameter) {
		OPERAND y = this->m_Tool.GetValue(this->m_ExpressionY, parameter);  //��ȡxֵ
		if (this->m_Tool.IsSuccess() == false) {  //�����Ƿ����
			if (this->m_Tool.GetError() == FUNC_ERROR_RANGE) {
				this->SetResult(true);  //���������򲻷��ش���ֱ�ӷ���INF
				return INF;
			}
			else {
				this->SetResult(false, this->m_Tool.GetError());  //�������󷵻�INV
				return INV;
			}
		}
		return y;
	}
}