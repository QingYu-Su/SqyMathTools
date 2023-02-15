// CAddNormalFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "FunctionIndicator.h"
#include "afxdialogex.h"
#include "CAddNormalFuncDlg.h"
#include "CFunctionDlg.h"


// CAddNormalFuncDlg 对话框

IMPLEMENT_DYNAMIC(CAddNormalFuncDlg, CDialogEx)

CAddNormalFuncDlg::CAddNormalFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_NORMALFUNC_DIALOG, pParent)
	, m_ExpressionStr(_T(""))
	, m_Precision(1000)
	, m_LineWidth(1)
	, m_LineType(PS_SOLID)
	, m_LineColor(RGB(0, 0, 0))
{
}

CAddNormalFuncDlg::~CAddNormalFuncDlg()
{
}

void CAddNormalFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FUNCTION, m_ExpressionStr);
	DDX_Text(pDX, IDC_EDIT_MIN, m_Left);
	DDX_Text(pDX, IDC_EDIT_MAX, m_Right);
	DDX_Text(pDX, IDC_EDIT_PRECISION, m_Precision);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, m_LineWidth);
	DDX_CBIndex(pDX, IDC_COMBO_LINE_TYPE, m_LineType);
}


BEGIN_MESSAGE_MAP(CAddNormalFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EDITFUNC, &CAddNormalFuncDlg::OnBnClickedButtonEditfunc)
	ON_BN_CLICKED(IDC_BUTTON_LINE_COLOR, &CAddNormalFuncDlg::OnBnClickedButtonPenColor)
END_MESSAGE_MAP()


// CAddNormalFuncDlg 消息处理程序


void CAddNormalFuncDlg::OnBnClickedButtonEditfunc()
{
	UpdateData();
	CFunctionDlg dlg('x');
	if (dlg.DoModal() == IDOK) {
		this->m_Expression = dlg.GetExpression();
		this->m_ExpressionStr = dlg.GetEditStr();
	}
	UpdateData(false);
}


void CAddNormalFuncDlg::OnBnClickedButtonPenColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_LineColor = dlg.GetColor();
	}
}
