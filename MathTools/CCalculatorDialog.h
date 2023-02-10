#pragma once
#include "afxdialogex.h"
#include <vector>
#include <string>
#include "Calculator.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")

// CCalculatorDialog 对话框

class CCalculatorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCalculatorDialog)

public:
	CCalculatorDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCalculatorDialog() {};

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
	std::vector<std::string> m_Expression;
	SqyMathLibrary::Calculator m_Calc;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNum0();
	afx_msg void OnBnClickedNum1();
	afx_msg void OnBnClickedNum2();
};
