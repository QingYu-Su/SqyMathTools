
// Demo2View.cpp: CDemo2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Demo2.h"
#endif

#include "Demo2Doc.h"
#include "Demo2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDemo2View

IMPLEMENT_DYNCREATE(CDemo2View, CView)

BEGIN_MESSAGE_MAP(CDemo2View, CView)
END_MESSAGE_MAP()

// CDemo2View 构造/析构

CDemo2View::CDemo2View() noexcept
{
	// TODO: 在此处添加构造代码

}

CDemo2View::~CDemo2View()
{
}

BOOL CDemo2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDemo2View 绘图

void CDemo2View::OnDraw(CDC* /*pDC*/)
{
	CDemo2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDemo2View 诊断

#ifdef _DEBUG
void CDemo2View::AssertValid() const
{
	CView::AssertValid();
}

void CDemo2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemo2Doc* CDemo2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo2Doc)));
	return (CDemo2Doc*)m_pDocument;
}
#endif //_DEBUG


// CDemo2View 消息处理程序
