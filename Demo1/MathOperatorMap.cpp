#include "MathOperatorMap.h"

namespace SqyMathLibrary {

	MathOperatorMap* MathOperatorMap::m_Instance = new MathOperatorMap();
	DestroyMathOperatorMap destroyMathOperatorMap;

	MathOperatorMap* MathOperatorMap::GetInstance() {
		return m_Instance;
	}

	MathOperatorMap::MathOperatorMap() {
		//Ä¬ÈÏÔËËã·û×¢²á
		this->Register("+", new Plus);
		this->Register("-", new Minus);
		this->Register("*", new Multiply);
		this->Register("/", new Divide);
		this->Register("(", new Left);
		this->Register(")", new Right);
		this->Register("^", new Pow);
		this->Register("%", new Mod);
		this->Register("sin", new Sin);
		this->Register("cos", new Cos);
		this->Register("tan", new Tan);
		this->Register("sqrt", new Sqrt);
		this->Register("log", new Log);
		this->Register("ln", new Ln);
		this->Register("1/x", new Reciprocal);
		this->Register("!", new Factorial);
		this->Register("+/-", new Negative);
		this->Register("abs", new Abs);
	}

	MathOperatorMap::~MathOperatorMap() {
		std::unordered_map< std::string, MathOperator* >::iterator it;
		for ( it = this->m_Map.begin(); it != this->m_Map.end(); it++) {
			delete it->second;
		}
	}

	MathOperator* MathOperatorMap::GetMathOperator(std::string key) {
		if (this->m_Map.find(key) != this->m_Map.end()) {
			return m_Map[key];
		}
		return NULL;
	}

	bool MathOperatorMap::Register(std::string key, MathOperator* val) {
		if (this->m_Map.find(key) != this->m_Map.end()) {
			return false;
		}
		this->m_Map[key] = val;
		return true;
	}

	void MathOperatorMap::Destroy(std::string key) {
		if (this->m_Map.find(key) == this->m_Map.end()) {
			return;
		}

		delete this->m_Map[key];
		this->m_Map[key] = NULL;

		this->m_Map.erase(key);
	}

}