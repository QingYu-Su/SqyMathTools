// CAddPolarFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "FunctionIndicator.h"
#include "afxdialogex.h"
#include "CAddPolarFuncDlg.h"
#include "CFunctionDlg.h"


// CAddPolarFuncDlg 对话框

IMPLEMENT_DYNAMIC(CAddPolarFuncDlg, CDialogEx)

CAddPolarFuncDlg::CAddPolarFuncDlg(double left, double right, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_POLARFUNC_DIALOG, pParent)
	, m_ExpressionStr(_T(""))
	, m_Precision(1000)
	, m_LineWidth(1)
	, m_LineType(PS_SOLID)
	, m_LineColor(RGB(0, 0, 0))
	, m_Left(left)
	, m_Right(right)
{

}

CAddPolarFuncDlg::~CAddPolarFuncDlg()
{
}

void CAddPolarFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FUNCTION, m_ExpressionStr);
	DDX_Text(pDX, IDC_EDIT_MIN, m_Left);
	DDX_Text(pDX, IDC_EDIT_MAX, m_Right);
	DDX_Text(pDX, IDC_EDIT_PRECISION, m_Precision);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, m_LineWidth);
	DDX_CBIndex(pDX, IDC_COMBO_LINE_TYPE, m_LineType);
}

SML::MathFunction* CAddPolarFuncDlg::GetMathFunction() {
	//创建极坐标函数表达式
	SML::FunctionExpression funcExpression(this->m_Expression, 'r', 'a', this->m_Left, this->m_Right);

	return new SML::PolarFunction(funcExpression); //返回极坐标函数对象

}

CString CAddPolarFuncDlg::GetExpressionStr() {
	return this->m_ExpressionStr;
}

size_t CAddPolarFuncDlg::GetPrecision() {
	return this->m_Precision;
}

double CAddPolarFuncDlg::GetMin() {
	return this->m_Left;
}

double CAddPolarFuncDlg::GetMax() {
	return this->m_Right;
}

int CAddPolarFuncDlg::GetLineWidth() {
	return this->m_LineWidth;
}

int CAddPolarFuncDlg::GetLineType() {
	return this->m_LineType;
}

COLORREF CAddPolarFuncDlg::GetLineColor() {
	return this->m_LineColor;
}



BEGIN_MESSAGE_MAP(CAddPolarFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EDITFUNC, &CAddPolarFuncDlg::OnBnClickedButtonEditfunc)
	ON_BN_CLICKED(IDC_BUTTON_LINE_COLOR, &CAddPolarFuncDlg::OnBnClickedButtonPenColor)
END_MESSAGE_MAP()

void CAddPolarFuncDlg::OnBnClickedButtonEditfunc()
{
	UpdateData();

	//弹出函数表达式编辑对话框
	CFunctionDlg dlg('a', this->m_Expression, this->m_ExpressionStr);
	if (dlg.DoModal() == IDOK) {
		this->m_Expression = dlg.GetExpression();  //同步函数表达式
		this->m_ExpressionStr = dlg.GetEditStr();  //同步函数表达式字符串
	}
	UpdateData(false);
}


void CAddPolarFuncDlg::OnBnClickedButtonPenColor()
{
	//弹出设置颜色对话框
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_LineColor = dlg.GetColor();
	}
}


// CAddPolarFuncDlg 消息处理程序
