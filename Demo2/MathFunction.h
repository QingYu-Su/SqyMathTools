/***************************************
     文件名：MathFunction.h
     作者：苏青羽
     功能描述：数学函数类
     创建日期：2023-02-11
     版本：v1.0
     最后修改日期：2022-02-11
***************************************/

#ifndef _MATHFUNCTION_H_
#define _MATHOFUNCTION_H_

#include <string>
#include "Calculator.h"
#include <vector>

namespace SqyMathLibrary {

    //函数表达式
    struct FunctionExpression {
        MathExpression m_Expression;
        char m_IV;  //因变量 
        char m_DV;  //自变量
        OPERAND m_MaxDV, m_MinDV;  //函数表达式定义域区间

        FunctionExpression(MathExpression &expression, char iv, char dv, OPERAND maxDV = INF, OPERAND minDV = -INF);
        OPERAND Calculate(OPERAND value);
    };

    typedef std::vector<FunctionExpression> Function;
    typedef std::pair<OPERAND, OPERAND> FunctionPoint;
    typedef std::vector<FunctionPoint> FPSet;

    enum FunctionType {
        Normal
    };

    class MathFunction {

    public: //类默认方法
        MathFunction(FunctionType type, Function &function, size_t accuracy);
        virtual ~MathFunction() {};
        //以下函数由编译器自动生成即可
        //MathFunction(const MathFunction&);
        //MathFunction& operator=(const MathFunction&);

    public:
        FunctionType GetType();
        Function GetFunction();
        size_t GetAccuracy();
        void SetFunction(Function &function);
        void SetAccuracy(size_t accuracy);
    protected:
        FunctionType m_Type;
        Function m_Function;
        size_t m_Accuracy;
    public:
        virtual FPSet Calculate(OPERAND xLeft, OPERAND xRight) = 0;
    };

    class NormalFunction :public MathFunction {
    public: //类默认方法
        NormalFunction(Function& function, size_t accuracy);
        virtual ~NormalFunction() {};
        //以下函数由编译器自动生成即可
        //NormalFunction(const NormalFunction&);
        //NormalFunction& operator=(const NormalFunction&);
    public:
        FPSet Calculate(OPERAND xLeft, OPERAND xRight);
    private:
        OPERAND GetY(OPERAND value);

    };

}





#endif