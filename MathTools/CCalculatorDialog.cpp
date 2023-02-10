// CCalculatorDialog.cpp: 实现文件
//

#include "pch.h"
#include "MathTools.h"
#include "afxdialogex.h"
#include "CCalculatorDialog.h"


// CCalculatorDialog 对话框

IMPLEMENT_DYNAMIC(CCalculatorDialog, CDialogEx)

CCalculatorDialog::CCalculatorDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR, pParent)
{

}

CCalculatorDialog::~CCalculatorDialog()
{
}

void CCalculatorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalculatorDialog, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDialog 消息处理程序
