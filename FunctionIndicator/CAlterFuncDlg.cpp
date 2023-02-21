// CAlterFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "FunctionIndicator.h"
#include "afxdialogex.h"
#include "CAlterFuncDlg.h"


// CAlterFuncDlg 对话框

IMPLEMENT_DYNAMIC(CAlterFuncDlg, CDialogEx)

CAlterFuncDlg::CAlterFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALTER_FUNC_DIALOG, pParent)
	, m_Num(1)
{

}

CAlterFuncDlg::~CAlterFuncDlg()
{
}

void CAlterFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ALTER_NUM, m_Num);
}

int CAlterFuncDlg::GetNum() {
	return this->m_Num;
}


BEGIN_MESSAGE_MAP(CAlterFuncDlg, CDialogEx)
END_MESSAGE_MAP()


// CAlterFuncDlg 消息处理程序
