#pragma once
#include "afxdialogex.h"


// CDelFuncDlg 对话框

class CDelFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDelFuncDlg)

public:
	CDelFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDelFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEL_FUNC_DIALOG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:

	DECLARE_MESSAGE_MAP()

public:
	int GetNum();
private:
	int m_Num;
};
