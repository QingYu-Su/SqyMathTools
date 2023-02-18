
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
	//释放函数链表空间
	if (!this->m_FunctionList.empty()) {
		std::list<SML::MathFunction*>::iterator it;
		for (it = this->m_FunctionList.begin(); it != this->m_FunctionList.end(); it++) {
			delete *it;
		}
	}

	//释放绘制函数链表空间
	if (!this->m_DrawDataList.empty()) {
		std::list<DrawFuncData*>::iterator it;
		for (it = this->m_DrawDataList.begin(); it != this->m_DrawDataList.end(); it++) {
			delete* it;
		}
	}
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

double CFunctionIndicatorDoc::GetMinX() {
	return this->m_MinX;
}

double CFunctionIndicatorDoc::GetMaxX() {
	return this->m_MaxX;
}

double CFunctionIndicatorDoc::GetMinY() {
	return this->m_MinY;
}

double CFunctionIndicatorDoc::GetMaxY() {
	return this->m_MaxY;
}

std::list<DrawFuncData*> CFunctionIndicatorDoc::GetDrawDataList() {
	return this->m_DrawDataList;
}


// CFunctionIndicatorDoc 命令


void CFunctionIndicatorDoc::OnAddNormalFunc()
{
	//弹出增加普通函数窗口，并将当前X范围设置为函数定义域初始值
	CAddNormalFuncDlg dlg(this->m_MinX, this->m_MaxX);
	if (dlg.DoModal() == IDOK) {

		//获得函数类对象
		SML::MathFunction* pFunction = dlg.GetMathFunction();
		
		//新建绘画数据，传入必要参数
		DrawFuncData* dfd = new DrawFuncData;
		dfd->precision = dlg.GetPrecision();

		//计算函数图像数据，范围为当前视图X轴范围，并将结果保存至绘画数据中
		dfd->drawPoint = pFunction->Calculate(this->m_MinX, this->m_MaxX, dfd->precision);
		
		//计算失败，弹出提示弹窗，释放相应资源并返回
		if (pFunction->IsSuccess() == false) {
			AfxMessageBox(pFunction->GetError().c_str());
			delete pFunction;
			delete dfd;
			return;
		}

		//将其他数据添加至绘画数据中
		dfd->expressionStr.push_back(CString("f(x)=") + dlg.GetExpressionStr());
		dfd->lineWidth = dlg.GetLineWidth();
		dfd->lineType = dlg.GetLineType();
		dfd->lineColor = dlg.GetLineColor();

		//将函数类对象和绘画数据添加至链表中保存
		this->m_FunctionList.push_back(pFunction);
		this->m_DrawDataList.push_back(dfd);
	}
	UpdateAllViews(NULL);
}
