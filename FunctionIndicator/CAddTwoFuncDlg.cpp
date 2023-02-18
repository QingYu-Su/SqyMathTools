// CAddTwoFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "FunctionIndicator.h"
#include "afxdialogex.h"
#include "CAddTwoFuncDlg.h"
#include "CFunctionDlg.h"


// CAddTwoFuncDlg 对话框

IMPLEMENT_DYNAMIC(CAddTwoFuncDlg, CDialogEx)

CAddTwoFuncDlg::CAddTwoFuncDlg(double left, double right, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_TWOFUNC_DIALOG, pParent)
	, m_Precision(1000)
	, m_LineWidth(1)
	, m_LineType(PS_SOLID)
	, m_LineColor(RGB(0, 0, 0))
	, m_Left(left)
	, m_Right(right)
	, m_ExpressionStrX(_T(""))
	, m_ExpressionStrY(_T(""))
{

}

CAddTwoFuncDlg::~CAddTwoFuncDlg()
{
}

void CAddTwoFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MIN, m_Left);
	DDX_Text(pDX, IDC_EDIT_MAX, m_Right);
	DDX_Text(pDX, IDC_EDIT_PRECISION, m_Precision);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, m_LineWidth);
	DDX_CBIndex(pDX, IDC_COMBO_LINE_TYPE, m_LineType);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_X, m_ExpressionStrX);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_Y, m_ExpressionStrY);
}

SML::MathFunction* CAddTwoFuncDlg::GetMathFunction() {
	//创建X(t)函数表达式
	SML::FunctionExpression funcExpressionX(this->m_ExpressionX, 'x', 't', this->m_Left, this->m_Right);

	//创建Y(t)函数表达式
	SML::FunctionExpression funcExpressionY(this->m_ExpressionY, 'y', 't', this->m_Left, this->m_Right);

	return new SML::TwoFunction(funcExpressionX, funcExpressionY); //返回参数方程函数对象

}

CString CAddTwoFuncDlg::GetExpressionStrX() {
	return this->m_ExpressionStrX;
}

CString CAddTwoFuncDlg::GetExpressionStrY() {
	return this->m_ExpressionStrY;
}

size_t CAddTwoFuncDlg::GetPrecision() {
	return this->m_Precision;
}

double CAddTwoFuncDlg::GetMin() {
	return this->m_Left;
}

double CAddTwoFuncDlg::GetMax() {
	return this->m_Right;
}

int CAddTwoFuncDlg::GetLineWidth() {
	return this->m_LineWidth;
}

int CAddTwoFuncDlg::GetLineType() {
	return this->m_LineType;
}

COLORREF CAddTwoFuncDlg::GetLineColor() {
	return this->m_LineColor;
}



BEGIN_MESSAGE_MAP(CAddTwoFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EDITFUNC_X, &CAddTwoFuncDlg::OnBnClickedButtonEditfuncX)
	ON_BN_CLICKED(IDC_BUTTON_EDITFUNC_Y, &CAddTwoFuncDlg::OnBnClickedButtonEditfuncY)
	ON_BN_CLICKED(IDC_BUTTON_LINE_COLOR, &CAddTwoFuncDlg::OnBnClickedButtonLineColor)
END_MESSAGE_MAP()


// CAddTwoFuncDlg 消息处理程序


void CAddTwoFuncDlg::OnBnClickedButtonEditfuncX()
{
	UpdateData();

	//弹出函数表达式编辑对话框
	CFunctionDlg dlg('t');
	if (dlg.DoModal() == IDOK) {
		this->m_ExpressionX = dlg.GetExpression();  //同步函数表达式
		this->m_ExpressionStrX = dlg.GetEditStr();  //同步函数表达式字符串
	}
	UpdateData(false);
}


void CAddTwoFuncDlg::OnBnClickedButtonEditfuncY()
{
	UpdateData();

	//弹出函数表达式编辑对话框
	CFunctionDlg dlg('t');
	if (dlg.DoModal() == IDOK) {
		this->m_ExpressionY = dlg.GetExpression();  //同步函数表达式
		this->m_ExpressionStrY = dlg.GetEditStr();  //同步函数表达式字符串
	}
	UpdateData(false);
}


void CAddTwoFuncDlg::OnBnClickedButtonLineColor()
{
	//弹出设置颜色对话框
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_LineColor = dlg.GetColor();
	}
}
