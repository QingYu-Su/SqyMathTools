/***************************************
     �ļ�����MathFunction.h
     ���ߣ�������
     ������������ѧ������
     �������ڣ�2023-02-11
     �汾��v1.0
     ����޸����ڣ�2022-02-13
***************************************/

#ifndef _MATHFUNCTION_H_
#define _MATHFUNCTION_H_

#include <string>
#include "Calculator.h"
#include <vector>
#include <map>

namespace SqyMathLibrary {

    //�������ʽ
    struct FunctionExpression {
        MathExpression m_Expression;
        char m_IV;  //����� 
        char m_DV;  //�Ա���
        OPERAND m_Left, m_Right;  //�������ʽ����������
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

    public: //��Ĭ�Ϸ���
        MathFunction(FunctionType type, Function &function);
        virtual ~MathFunction() {};
        //���º����ɱ������Զ����ɼ���
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
        FPMap m_FPMap;  //��ǰ������ͼ���,��ʵʱ����
        OPERAND m_MinX, m_MaxX;  //������x���ϵļ�ֵ����ʵʱ����
        OPERAND m_MinY, m_MaxY;  //������y���ϵļ�ֵ����ʵʱ����
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
    public: //��Ĭ�Ϸ���
        NormalFunction(Function& function);
        virtual ~NormalFunction() {};
        //���º����ɱ������Զ����ɼ���
        //NormalFunction(const NormalFunction&);
        //NormalFunction& operator=(const NormalFunction&);
    protected:
        bool IsValid();
    public:
        bool Calculate(OPERAND minDV, OPERAND maxDV, size_t precision);
    };

    class PolarFunction :public MathFunction {
    public: //��Ĭ�Ϸ���
        PolarFunction(Function& function);
        virtual ~PolarFunction() {};
        //���º����ɱ������Զ����ɼ���
        //PolarFunction(const PolarFunction&);
        //PolarFunction& operator=(const PolarFunction&);
        bool IsValid();
    public:
        bool Calculate(OPERAND minDV, OPERAND maxDV, size_t precision);
    };

    class ParaFunction :public MathFunction {
    public: //��Ĭ�Ϸ���
        ParaFunction(Function& function);
        virtual ~ParaFunction() {};
        //���º����ɱ������Զ����ɼ���
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