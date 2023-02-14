/***************************************
     �ļ�����CFunctionData.h
     ���ߣ�������
     ��������������������
     �������ڣ�2023-02-14
     �汾��v1.0
     ����޸����ڣ�2022-02-14
***************************************/

#ifndef _CFUNCTIONDATA_H_
#define _CFUNCTIONDATA_H_

#include "pch.h"
#include "framework.h"
#include "MathFunction.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
namespace SML = SqyMathLibrary;  //�����ռ�������

class CFunctionData : public CObject {
public:  //��Ĭ�Ϸ���
    CFunctionData(SML::MathFunction* function, int penWidth = 1, int penType = PS_SOLID, COLORREF penColor = RGB(0, 0, 0));
    ~CFunctionData();

    //���º����ɱ������Զ����ɼ���
    //CFunctionData(const CFunctionData&) {};
    //CFunctionData& operator=(const CFunctionData&) {};

public:  //��������
    int GetPenWidth();
    int GetPenType();
    COLORREF GetPenColor();
    SML::FunctionMap GetFunctionMap(OPERAND left, OPERAND right);

private:
    SML::MathFunction *m_Function;  //����
    int m_PenWidth;			//���ʿ��
    int m_PenType;			//��������
    COLORREF m_PenColor;		//������ɫ
    size_t m_Precision;   //������ϸ��
};

#endif
