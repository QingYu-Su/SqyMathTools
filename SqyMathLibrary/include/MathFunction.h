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

    typedef std::pair<OPERAND, OPERAND> FunctionPoint;
    typedef std::vector<FunctionPoint> FunctionMap;

    //函数表达式
    struct FunctionExpression {
        MathExpression m_Expression;
        char m_IV;  //因变量 
        char m_DV;  //自变量
        OPERAND m_Left, m_Right;  //函数表达式定义域区间
        FunctionExpression(MathExpression& expression, char iv, char dv, OPERAND left = -INF, OPERAND right = INF);
    };

    enum FunctionType {
        Normal
    };

    class FunctionTool {
    public:
        void TranslateExpression(FunctionExpression& fe, char key, OPERAND value );
        OPERAND GetValue(FunctionExpression fe, OPERAND parameter);
        bool IsSuccess();
        std::string GetError();
    private:
        std::string m_Error;
        bool m_Success;
    };

    class MathFunction {
    public:
        bool Calculate(OPERAND left, OPERAND right, size_t precision);
        std::string GetError();
    protected:
        virtual bool IsValid() = 0;
        virtual bool PreProcess() {};
        virtual OPERAND GetX(OPERAND parameter) = 0;
        virtual OPERAND GetY(OPERAND parameter) = 0;
        virtual bool PostProcess() {};
        void SetError(std::string error);
        FunctionTool m_Tool;
    private:
        FunctionType m_Type;
        OPERAND m_MinX, m_MaxX;
        OPERAND m_MinY, m_MaxY;
        FunctionMap m_Map;
        std::string m_Error;
    };

    class NormalFunction :public MathFunction {
    protected:
        bool IsValid();
        OPERAND GetX(OPERAND parameter);
        OPERAND GetY(OPERAND parameter);
    private:
        FunctionExpression m_Expression;
    };

    class PolarFunction :public MathFunction {
    protected:
        bool IsValid();
        OPERAND GetX(OPERAND parameter);
        OPERAND GetY(OPERAND parameter);
    private:
        OPERAND GetR(OPERAND parameter);
        FunctionExpression m_Expression;
    };

    class TwoFunction :public MathFunction {
    protected:
        bool IsValid();
        OPERAND GetX(OPERAND parameter);
        OPERAND GetY(OPERAND parameter);
    private:
        FunctionExpression m_ExpressionX;
        FunctionExpression m_ExpressionY;
    };
}





#endif