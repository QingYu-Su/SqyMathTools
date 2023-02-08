/***************************************
     �ļ�����Calculator.h
     ���ߣ�������
     ������������ѧ���ʽ����
     �������ڣ�2023-02-06
     �汾��v1.0
     ����޸����ڣ�2022-02-06
***************************************/

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <string>
#include <stack>
#include <vector>
#include "MathOperatorMap.h"

namespace SqyMathLibrary {

    class Calculator {

    public:  //��Ĭ�Ϸ���
        Calculator();

        //���º����ɱ������Զ����ɼ���
        //~Calculator() {};
        //Calculator(const Calculator&) {};
        //Calculator& operator=(const Calculator&) {};

    public:
        OPERAND Calculate(const std::vector<std::string> &expression);
        bool IsSuccess() const;  //�����Ƿ�ɹ�
        std::string GetError() const;  //��ȡ����ʧ��ԭ��

    private:
        bool IsNum( const std::string &s) const;
        bool IsOperator(const std::string &s) const;
        OPERAND GetNum(const std::string &s) const;
        MathOperator* GetMathOperator(const std::string &s) const;
        bool Operate();
        void SetResult(bool res, std::string reason = "");  //����������
        OPERAND Reset(); //��ռ�����

        
    private:
        std::stack<OPERAND> m_Nums;
        std::stack<MathOperator*> m_MathOpts;
        bool m_Success;  //��һ������Ľ��
        std::string m_Error;  //����һ������ʧ�ܣ��ᱣ����һ������ʧ�ܵ�ԭ��
    
    };

}




#endif


