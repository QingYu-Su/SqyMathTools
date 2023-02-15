/***************************************
     �ļ�����MathFunction.h
     ���ߣ�������
     ������������ѧ����
     �������ڣ�2023-02-11
     �汾��v1.0
     ����޸����ڣ�2022-02-13
***************************************/

#ifndef _MATHFUNCTION_H_
#define _MATHFUNCTION_H_

#include "UniFunction.h"

namespace SqyMathLibrary {

    typedef std::pair<OPERAND, OPERAND> FunctionPoint;  //������

    typedef std::vector<FunctionPoint> FunctionMap;  //����ͼ��

    enum FunctionType {  //��������
        Normal,  //��ͨ����
        Polar,  //�����꺯��
        Two  //�������̺���
    };

    //��ѧ�����࣬����ʾ��һ��������XYƽ������ʾ��Ӧͼ��ĺ���
    class MathFunction {
    public: //��Ĭ�Ϸ���
        MathFunction(FunctionType type);
        virtual ~MathFunction() {};

        //���º����ɱ������Զ����ɼ���
        //MathFunction(const MathFunction&) {};
        //MathFunction& operator=(const MathFunction&) {};
    public:
        //�����ض������ϵ�����X-Yƽ���ϵĺ����㡣����������Ϊ����������������Ӧ�˺�����ľ�ϸ��
        //ע�⣬��������Ķ��岢���̶��������Ա����Ķ�����ı䣬����ͨ����������x�ϵ����䣬�������̺���������t�ϵ����䣬�����꺯�����ڽǶ��ϵ�����
        //����ֵ�п���ΪINF������һ����Чֵ������ʾ�õ���y�����޶���
        //������ʧ�ܣ��򷵻ؿ�FunctionMap
        FunctionMap Calculate(OPERAND left, OPERAND right, size_t precision);

        bool IsSuccess();  //�����Ƿ�ɹ� 
        std::string GetError();   //��������ʧ��ԭ��
    
    protected://����ʹ���˲���ģʽ�����·���������ʵ�֣�������������ʹ��
        virtual bool IsValid() = 0;  //�����Ƿ���Ч������������ʵ��
        virtual bool PreProcess() {};  //����֮ǰ��Ԥ������û���򲻱�ʵ��
        virtual OPERAND GetX(OPERAND parameter) = 0;  //��ȡ�����Ա�����ĳ��ֵ��x���ϵĶ�Ӧֵ������������ʵ�֣�����INV��ʾ����ʧ��
        virtual OPERAND GetY(OPERAND parameter) = 0;  //��ȡ�����Ա�����ĳ��ֵ��y���ϵĶ�Ӧֵ������������ʵ�֣�����INV��ʾ����ʧ��
        virtual bool PostProcess() {}; //����֮��ĺ�����û���򲻱�ʵ��

    protected:
        void SetResult(bool res, std::string reason = "");  //���ò����ɹ����
    private:
        FunctionType m_Type;  //��������
        OPERAND m_MinX, m_MaxX;  //������X���ϵļ�ֵ��������Calculate��ʹ�ö�����
        OPERAND m_MinY, m_MaxY;  //������Y���ϵļ�ֵ��������CalCulate��ʹ�ö�����
        bool m_Success;  //��һ�β����Ľ��
        std::string m_Error; //����һ�β���ʧ�ܣ��ᱣ����һ�β���ʧ�ܵ�ԭ��
    };

    //��ͨ����
    class NormalFunction :public MathFunction {
    public://��Ĭ�Ϸ���
        NormalFunction(FunctionExpression &expression);
        virtual ~NormalFunction() {};

        //���º����ɱ������Զ����ɼ���
        //MathFunction(const MathFunction&) {};
        //MathFunction& operator=(const MathFunction&) {};
    protected:  //���෽��������ʵ��
        bool IsValid();
        OPERAND GetX(OPERAND parameter);
        OPERAND GetY(OPERAND parameter);
    private:
        FunctionExpression m_Expression;  //���庯������ʽ����ʾF(x) = y;
        FunctionTool m_Tool;  //������������ʽ�Ĺ���
    };

    //�����꺯��
    class PolarFunction :public MathFunction {
    public://��Ĭ�Ϸ���
        PolarFunction(FunctionExpression& expression);
        virtual ~PolarFunction() {};
        //���º����ɱ������Զ����ɼ���
        //PolarFunction(const PolarFunction&) {};
        //PolarFunction& operator=(const PolarFunction&) {};
    protected: //���෽��������ʵ��
        bool IsValid();
        OPERAND GetX(OPERAND parameter);
        OPERAND GetY(OPERAND parameter);
    private:
        OPERAND GetR(OPERAND parameter);  //��ȡĳ���ض��Ƕȶ�Ӧ��rֵ
        FunctionExpression m_Expression;  //���庯������ʽ����ʾF(a) = r;
        FunctionTool m_Tool;  //������������ʽ�Ĺ���
    };

    class TwoFunction :public MathFunction {
    public://��Ĭ�Ϸ���
        TwoFunction(FunctionExpression& expressionX, FunctionExpression& expressionY);
        virtual ~TwoFunction() {};
        //���º����ɱ������Զ����ɼ���
        //TwoFunction(const TwoFunction&) {};
        //TwoFunction& operator=(const TwoFunction&) {};
    protected://���෽��������ʵ��
        bool IsValid();
        OPERAND GetX(OPERAND parameter);
        OPERAND GetY(OPERAND parameter);
    private:
        FunctionExpression m_ExpressionX;  //���庯������ʽ,��ʾF(t) = x;
        FunctionExpression m_ExpressionY;  //���庯������ʽ,��ʾF(t) = y;
        FunctionTool m_Tool;  //������������ʽ�Ĺ���
    };
}





#endif