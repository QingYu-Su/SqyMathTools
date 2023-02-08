/***************************************
     文件名：Calculator.h
     作者：苏青羽
     功能描述：数学表达式计算
     创建日期：2023-02-06
     版本：v1.0
     最后修改日期：2022-02-06
***************************************/

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <string>
#include <stack>
#include <vector>
#include "MathOperatorMap.h"

namespace SqyMathLibrary {

    class Calculator {

    public:  //类默认方法
        Calculator();

        //以下函数由编译器自动生成即可
        //~Calculator() {};
        //Calculator(const Calculator&) {};
        //Calculator& operator=(const Calculator&) {};

    public:
        OPERAND Calculate(const std::vector<std::string> &expression);
        bool IsSuccess() const;  //运算是否成功
        std::string GetError() const;  //获取运算失败原因

    private:
        bool IsNum( const std::string &s) const;
        bool IsOperator(const std::string &s) const;
        OPERAND GetNum(const std::string &s) const;
        MathOperator* GetMathOperator(const std::string &s) const;
        bool Operate();
        void SetResult(bool res, std::string reason = "");  //设置运算结果
        OPERAND Reset(); //清空计算器

        
    private:
        std::stack<OPERAND> m_Nums;
        std::stack<MathOperator*> m_MathOpts;
        bool m_Success;  //上一次运算的结果
        std::string m_Error;  //若上一次运算失败，会保存上一次运算失败的原因
    
    };

}




#endif


