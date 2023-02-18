﻿#pragma once
#include "afxdialogex.h"
#include "../SqyMathLibrary/include/MathFunction.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
namespace SML = SqyMathLibrary;  //命名空间重命名


// CAddPolarFuncDlg 对话框

class CAddPolarFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPolarFuncDlg)

public:
	CAddPolarFuncDlg(double left, double right, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddPolarFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_POLARFUNC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	SML::MathFunction* GetMathFunction();  //获得函数类对象
	CString GetExpressionStr();  //返回函数表达式字符串
	size_t GetPrecision();  //获得函数精度
	double GetMin();  //获得函数定义域左端点
	double GetMax();  //获得函数定义域右端点
	int GetLineWidth();  //获得线宽
	int GetLineType();  //获得线型
	COLORREF GetLineColor();  //获得线颜色

private:
	SML::MathExpression m_Expression;  //函数表达式
	CString m_ExpressionStr;  //函数表达式字符串
	double m_Left, m_Right;  //函数定义域
	size_t m_Precision;  //图像精细度
	int m_LineWidth;  //线宽
	int m_LineType;  //线型
	COLORREF m_LineColor;  //线颜色

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEditfunc();
	afx_msg void OnBnClickedButtonPenColor();
};