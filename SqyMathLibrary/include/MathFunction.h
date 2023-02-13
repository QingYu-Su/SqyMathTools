/***************************************
     文件名：MathFunction.h
     作者：苏青羽
     功能描述：数学函数类
     创建日期：2023-02-11
     版本：v1.0
     最后修改日期：2022-02-13
***************************************/

#ifndef _MATHFUNCTION_H_
#define _MATHFUNCTION_H_

#include <string>
#include "Calculator.h"
#include <vector>
#include <map>

namespace SqyMathLibrary {

    //函数表达式
    struct FunctionExpression {
        MathExpression m_Expression;
        char m_IV;  //因变量 
        char m_DV;  //自变量
        OPERAND m_Left, m_Right;  //函数表达式定义域区间
        FunctionExpression(MathExpression& expression, char iv, char dv, OPERAND left = -INF, OPERAND right = INF);
    };

    typedef std::vector<FunctionExpression> Function;
    typedef std::pair<OPERAND, OPERAND> FunctionPoint;
    typedef std::vector<FunctionPoint> FPMap;

    enum FunctionType {
        Normal,
        Polar,
        Parametric
    };

    class MathFunction {

    public: //类默认方法
        MathFunction(FunctionType type, Function &function);
        virtual ~MathFunction() {};
        //以下函数由编译器自动生成即可
        //MathFunction(const MathFunction&);
        //MathFunction& operator=(const MathFunction&);

    public:
        FunctionType GetType();
        Function GetFunction();
        void SetFunction(Function &function);
        std::string GetError();
    protected:
        FunctionType m_Type;
        Function m_Function;
        FPMap m_FPMap;  //当前函数的图像点,会实时更新
        OPERAND m_MinX, m_MaxX;  //函数在x轴上的极值，会实时更新
        OPERAND m_MinY, m_MaxY;  //函数在y轴上的极值，会实时更新
        std::string m_Error;
        Calculator m_Calc;
    protected:
        void TranslateExpression(MathExpression& me, char c, OPERAND value);
        OPERAND GetValue(OPERAND parameter, int index);
        virtual bool IsValid() {};
        virtual void Pretreat();
    public:
        virtual bool Calculate( OPERAND minDV, OPERAND maxDV, size_t precision) = 0;
    };

    class NormalFunction :public MathFunction {
    public: //类默认方法
        NormalFunction(Function& function);
        virtual ~NormalFunction() {};
        //以下函数由编译器自动生成即可
        //NormalFunction(const NormalFunction&);
        //NormalFunction& operator=(const NormalFunction&);
    protected:
        bool IsValid();
    public:
        bool Calculate(OPERAND minDV, OPERAND maxDV, size_t precision);
    };

    class PolarFunction :public MathFunction {
    public: //类默认方法
        PolarFunction(Function& function);
        virtual ~PolarFunction() {};
        //以下函数由编译器自动生成即可
        //PolarFunction(const PolarFunction&);
        //PolarFunction& operator=(const PolarFunction&);
        bool IsValid();
    public:
        bool Calculate(OPERAND minDV, OPERAND maxDV, size_t precision);
    };

    class ParaFunction :public MathFunction {
    public: //类默认方法
        ParaFunction(Function& function);
        virtual ~ParaFunction() {};
        //以下函数由编译器自动生成即可
        //ParaFunction(const ParaFunction&);
        //ParaFunction& operator=(const ParaFunction&);
    public:
        bool Calculate(OPERAND minDV, OPERAND maxDV, size_t precision);
        bool IsValid();
        void Pretreat();
    private:
        Function m_XFunction;
        Function m_YFunction;
    };
}





#endif