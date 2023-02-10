#pragma once
#include "afxdialogex.h"


// CCalculatorDialog 对话框

class CCalculatorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCalculatorDialog)

public:
	CCalculatorDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCalculatorDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCalculatorDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
