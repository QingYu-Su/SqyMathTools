// CDelFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "FunctionIndicator.h"
#include "afxdialogex.h"
#include "CDelFuncDlg.h"


// CDelFuncDlg 对话框

IMPLEMENT_DYNAMIC(CDelFuncDlg, CDialogEx)

CDelFuncDlg::CDelFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEL_FUNC_DIALOG, pParent)
	, m_Num(1)
{

}

CDelFuncDlg::~CDelFuncDlg()
{
}

void CDelFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEL_NUM, m_Num);
}

int CDelFuncDlg::GetNum() {
	return this->m_Num;
}

BEGIN_MESSAGE_MAP(CDelFuncDlg, CDialogEx)
END_MESSAGE_MAP()


// CDelFuncDlg 消息处理程序
