﻿
// MathToolsView.cpp: CMathToolsView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MathTools.h"
#endif

#include "MathToolsDoc.h"
#include "MathToolsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMathToolsView

IMPLEMENT_DYNCREATE(CMathToolsView, CView)

BEGIN_MESSAGE_MAP(CMathToolsView, CView)
END_MESSAGE_MAP()

// CMathToolsView 构造/析构

CMathToolsView::CMathToolsView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMathToolsView::~CMathToolsView()
{
}

BOOL CMathToolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMathToolsView 绘图

void CMathToolsView::OnDraw(CDC* /*pDC*/)
{
	CMathToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMathToolsView 诊断

#ifdef _DEBUG
void CMathToolsView::AssertValid() const
{
	CView::AssertValid();
}

void CMathToolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMathToolsDoc* CMathToolsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMathToolsDoc)));
	return (CMathToolsDoc*)m_pDocument;
}
#endif //_DEBUG


// CMathToolsView 消息处理程序
