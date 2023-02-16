#pragma once
#include "afxdialogex.h"
#include "MathFunction.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
namespace SML = SqyMathLibrary;  //命名空间重命名


// CAddNormalFuncDlg 对话框

class CAddNormalFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNormalFuncDlg)

public:
	CAddNormalFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddNormalFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_NORMALFUNC_DIALOG };
#endif

public:
	SML::MathFunction* GetMathFunction();  //获得函数
	size_t GetPrecision();  //获得函数精度
	int GetLineWidth();  //获得线宽
	int GetLineType();  //获得线型
	COLORREF GetLineColor();  //获得线颜色

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
	SML::MathExpression m_Expression;
	CString m_ExpressionStr;
	OPERAND m_Left;
	OPERAND m_Right;
	size_t m_Precision;
	int m_LineWidth;
	int m_LineType;
	COLORREF m_LineColor;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEditfunc();
	afx_msg void OnBnClickedButtonPenColor();
};
