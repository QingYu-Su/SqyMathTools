
// CCalculatorDlg.h: 头文件
//

#pragma once
#include "Calculator.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
namespace SML = SqyMathLibrary;

// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	bool IsNewNum();

private:
	SML::Calculator m_Calculator;
	std::vector<std::string> m_Expression;
	CString m_Current;
	CString m_Histroy;
	
public:
	afx_msg void OnBnClickedNum0();
	afx_msg void OnBnClickedNum1();
	afx_msg void OnBnClickedNum2();
	afx_msg void OnBnClickedNum3();
	afx_msg void OnBnClickedNum4();
	afx_msg void OnBnClickedNum5();
	afx_msg void OnBnClickedNum6();
	afx_msg void OnBnClickedNum7();
	afx_msg void OnBnClickedNum8();
	afx_msg void OnBnClickedNum9();
	afx_msg void OnBnClickedCalcDot();
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedMultiply();
	afx_msg void OnBnClickedDivide();
	afx_msg void OnBnClickedPow();
	afx_msg void OnBnClickedMod();
	afx_msg void OnBnClickedSin();
	afx_msg void OnBnClickedCos();
	afx_msg void OnBnClickedTan();
	afx_msg void OnBnClickedSqrt();
	afx_msg void OnBnClickedLog();
	afx_msg void OnBnClickedLn();
	afx_msg void OnBnClickedReciproal();
	afx_msg void OnBnClickedFactorial();
	afx_msg void OnBnClickedNegative();
	afx_msg void OnBnClickedE();
	afx_msg void OnBnClickedPi();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedAbs();
	afx_msg void OnBnClickedEqual();
	afx_msg void OnBnClickedAllclear();
	afx_msg void OnBnClickedDelete();
};
