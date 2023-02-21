#pragma once
#include "afxdialogex.h"


// CAlterFuncDlg 对话框

class CAlterFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlterFuncDlg)

public:
	CAlterFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAlterFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALTER_FUNC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	int GetNum();


	DECLARE_MESSAGE_MAP()
private:
	int m_Num;
};
