/***************************************
     �ļ�����MathFunction.h
     ���ߣ�������
     ������������ѧ������
     �������ڣ�2023-02-11
     �汾��v1.0
     ����޸����ڣ�2022-02-11
***************************************/

#ifndef _MATHFUNCTION_H_
#define _MATHOFUNCTION_H_

#include <string>
#include "Calculator.h"
#include <vector>

namespace SqyMathLibrary {

    struct FunctionExpression {
        std::vector<std::string> m_Expression;
        char m_IV;  //����� 
        char m_DV;  //�Ա���
        OPERAND m_MaxDV, m_MinDV;

        FunctionExpression(std::vector<std::string> expression, char iv, char dv, OPERAND maxDV = INF, OPERAND minDV = -INF);
        OPERAND Calculate(OPERAND value);
    };

    typedef std::vector<FunctionExpression> Function;
    typedef std::pair<OPERAND, OPERAND> FunctionPoint;
    typedef std::vector<FunctionPoint> FPSet;

    enum FunctionType {
        Normal
    };

    class MathFunction {

    public: //��Ĭ�Ϸ���
        MathFunction(FunctionType type, Function &function, size_t accuracy);
        virtual ~MathFunction() {};
        //���º����ɱ������Զ����ɼ���
        //MathFunction(const MathFunction&);
        //MathFunction& operator=(const MathFunction&);

    public:
        FunctionType GetType();
        Function GetFunction();
        size_t GetAccuracy();
        void SetFunction(Function &function);
        void SetAccuracy(size_t accuracy);
    private:
        FunctionType m_Type;
        Function m_Function;
        size_t m_Accuracy;
    public:
        virtual FPSet Calculate(OPERAND xLeft, OPERAND xRight) = 0;
    };



}





#endif