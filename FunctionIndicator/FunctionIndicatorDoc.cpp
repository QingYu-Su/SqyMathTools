﻿
// FunctionIndicatorDoc.cpp: CFunctionIndicatorDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FunctionIndicator.h"
#endif

#include "FunctionIndicatorDoc.h"
#include "CAddNormalFuncDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFunctionIndicatorDoc

IMPLEMENT_DYNCREATE(CFunctionIndicatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CFunctionIndicatorDoc, CDocument)
	ON_COMMAND(ID_ADD_NORMAL_FUNC, &CFunctionIndicatorDoc::OnAddNormalFunc)
END_MESSAGE_MAP()


// CFunctionIndicatorDoc 构造/析构

CFunctionIndicatorDoc::CFunctionIndicatorDoc() noexcept
{
	this->m_ShowGrid = true;
	this->m_ShowAxis = true;
	this->m_ShowEdge = true;
	this->m_SingelMode = true;
	this->m_FixedXRange = false;
	this->m_ShowPoint = false;
	this->m_MinX = -10;
	this->m_MaxX = 10;
	this->m_MinY = -1;
	this->m_MaxY = 1;

}

CFunctionIndicatorDoc::~CFunctionIndicatorDoc()
{
}

BOOL CFunctionIndicatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CFunctionIndicatorDoc 序列化

void CFunctionIndicatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CFunctionIndicatorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CFunctionIndicatorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CFunctionIndicatorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFunctionIndicatorDoc 诊断

#ifdef _DEBUG
void CFunctionIndicatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFunctionIndicatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFunctionIndicatorDoc 命令


void CFunctionIndicatorDoc::OnAddNormalFunc()
{
	CAddNormalFuncDlg dlg;
	if (dlg.DoModal() == IDOK) {
		AfxMessageBox("成功退出");
	}
}
