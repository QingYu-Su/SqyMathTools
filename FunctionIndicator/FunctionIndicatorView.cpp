
// FunctionIndicatorView.cpp: CFunctionIndicatorView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FunctionIndicator.h"
#endif

#include "FunctionIndicatorDoc.h"
#include "FunctionIndicatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFunctionIndicatorView

IMPLEMENT_DYNCREATE(CFunctionIndicatorView, CView)

BEGIN_MESSAGE_MAP(CFunctionIndicatorView, CView)
END_MESSAGE_MAP()

// CFunctionIndicatorView 构造/析构

CFunctionIndicatorView::CFunctionIndicatorView() noexcept
{
	// TODO: 在此处添加构造代码

}

CFunctionIndicatorView::~CFunctionIndicatorView()
{
}

BOOL CFunctionIndicatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFunctionIndicatorView 绘图

void CFunctionIndicatorView::OnDraw(CDC* /*pDC*/)
{
	CFunctionIndicatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CFunctionIndicatorView 诊断

#ifdef _DEBUG
void CFunctionIndicatorView::AssertValid() const
{
	CView::AssertValid();
}

void CFunctionIndicatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFunctionIndicatorDoc* CFunctionIndicatorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFunctionIndicatorDoc)));
	return (CFunctionIndicatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CFunctionIndicatorView 消息处理程序
