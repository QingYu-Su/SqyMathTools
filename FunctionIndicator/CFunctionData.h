/***************************************
     文件名：CFunctionData.h
     作者：苏青羽
     功能描述：函数数据类
     创建日期：2023-02-14
     版本：v1.0
     最后修改日期：2022-02-14
***************************************/

#ifndef _CFUNCTIONDATA_H_
#define _CFUNCTIONDATA_H_

#include "pch.h"
#include "framework.h"
#include "MathFunction.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
namespace SML = SqyMathLibrary;  //命名空间重命名

class CFunctionData : public CObject {
public:  //类默认方法
    CFunctionData(SML::MathFunction* function, int penWidth = 1, int penType = PS_SOLID, COLORREF penColor = RGB(0, 0, 0));
    ~CFunctionData();

    //以下函数由编译器自动生成即可
    //CFunctionData(const CFunctionData&) {};
    //CFunctionData& operator=(const CFunctionData&) {};

public:  //基本方法
    int GetPenWidth();
    int GetPenType();
    COLORREF GetPenColor();
    SML::FunctionMap GetFunctionMap(OPERAND left, OPERAND right);

private:
    SML::MathFunction *m_Function;  //函数
    int m_PenWidth;			//画笔宽度
    int m_PenType;			//画笔类型
    COLORREF m_PenColor;		//画笔颜色
    size_t m_Precision;   //函数精细度
};

#endif
