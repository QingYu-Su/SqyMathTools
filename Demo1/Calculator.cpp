#include "Calculator.h"

namespace SqyMathLibrary {

	Calculator::Calculator() {
		this->m_Success = true;
		this->m_Error = "";
	}

	bool Calculator::IsSuccess() const {
		return this->m_Success;
	}

	std::string Calculator::GetError() const {
		return this->m_Error;
	}

	bool Calculator::IsNum(const std::string& s) const{
		int dot = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '.') {
				dot++;
				continue;
			}
			if (s[i] < '0' || s[i] > '9') {
				return false;
			}
		}
		if (dot > 1) return false;
		return true;
	}

	bool Calculator::IsOperator(const std::string& s) const{
		if (GET_MATH_OPERATOR(s) == NULL) return false;
		return true;
	}

	OPERAND Calculator::GetNum(const std::string& s) const{
		return stod(s);
	}

	MathOperator* Calculator::GetMathOperator(const std::string& s) const{
		return GET_MATH_OPERATOR(s);
	}

	bool Calculator::Operate() {
		if (this->m_MathOpts.empty() == true || this->m_Nums.size() < 2 ) return false;

		OPERAND first = this->m_Nums.top();
		this->m_Nums.pop();

		OPERAND second = this->m_Nums.top();
		this->m_Nums.pop();

		MathOperator* opt = this->m_MathOpts.top();
		this->m_MathOpts.pop();

		this->m_Nums.push(opt->Operate(second, first));

		if (opt->IsSuccess() == false) {
			this->SetResult(false, opt->GetError());
			return false;
		}
		
		return true;
	}

	void Calculator::SetResult(bool res, std::string reason) {
		this->m_Success = res;
		this->m_Error = reason;
	}


	OPERAND Calculator::Calculate(const std::vector<std::string>& expression) {
		for (int i = 0; i < expression.size(); i++) {

			if (this->IsNum(expression[i]) == true) {
				this->m_Nums.push(this->GetNum(expression[i]));
			}
			else if (this->IsOperator(expression[i]) == true) {

				MathOperator* opt = this->GetMathOperator(expression[i]);
				
				if (opt -> GetSymbol() == ")") {

					while ( this->m_MathOpts.top()->GetSymbol() != "(" ) {
						if (this->Operate() == false) break;
						this->m_MathOpts.pop();
					}

				}
				else {

					while (opt->GetPriority() <= this->m_MathOpts.top()->GetPriority()) {
						if (this->m_MathOpts.top()->GetSymbol() == "(") break;
						if (this->Operate() == false) break;
					}

					if (this->m_Success == true) this->m_MathOpts.push(opt);

				}
			}
			else {
				this->SetResult(false, "表达式违法");
				return 0;
			}

			if (this->m_Success == false) return 0;
		}

		while (!this->m_MathOpts.empty()) {
			if (this->Operate() == false) return 0;
		}

		OPERAND res = this->m_Nums.top();
		this->m_Nums.pop();

		if (!this->m_Nums.empty()) return 0;

		return res;
	}

	OPERAND Calculator::Reset() {
		while (!this->m_Nums.empty()) this->m_Nums.pop();
		while (!this->m_MathOpts.empty()) this->m_MathOpts.pop();
		return 0;
	}

}