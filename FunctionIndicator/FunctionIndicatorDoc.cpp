
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
#include "CAddPolarFuncDlg.h"
#include "CAddTwoFuncDlg.h"
#include "CDelFuncDlg.h"
#include "CSetXYRangeDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFunctionIndicatorDoc

IMPLEMENT_DYNCREATE(CFunctionIndicatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CFunctionIndicatorDoc, CDocument)
	ON_COMMAND(ID_ADD_NORMAL_FUNC, &CFunctionIndicatorDoc::OnAddNormalFunc)
	ON_COMMAND(ID_ADD_POLAR_FUNC, &CFunctionIndicatorDoc::OnAddPolarFunc)
	ON_COMMAND(ID_ADD_TWO_FUNC, &CFunctionIndicatorDoc::OnAddTwoFunc)
	ON_COMMAND(ID_DEL_FUNC, &CFunctionIndicatorDoc::OnDelFunc)
	ON_COMMAND(ID_DEL_ALL_FUNC, &CFunctionIndicatorDoc::OnDelAllFunc)
	ON_COMMAND(ID_SET_XY_RANGE, &CFunctionIndicatorDoc::OnSetXyRange)
	ON_COMMAND(ID_EDGE, &CFunctionIndicatorDoc::OnEdge)
	ON_COMMAND(ID_AXIS, &CFunctionIndicatorDoc::OnAxis)
	ON_COMMAND(ID_GRID, &CFunctionIndicatorDoc::OnGrid)
	ON_UPDATE_COMMAND_UI(ID_EDGE, &CFunctionIndicatorDoc::OnUpdateEdge)
	ON_UPDATE_COMMAND_UI(ID_AXIS, &CFunctionIndicatorDoc::OnUpdateAxis)
	ON_UPDATE_COMMAND_UI(ID_GRID, &CFunctionIndicatorDoc::OnUpdateGrid)
	ON_COMMAND(ID_MOVE, &CFunctionIndicatorDoc::OnMove)
	ON_UPDATE_COMMAND_UI(ID_MOVE, &CFunctionIndicatorDoc::OnUpdateMove)
	ON_COMMAND(ID_FUNC_INFO, &CFunctionIndicatorDoc::OnFuncInfo)
	ON_UPDATE_COMMAND_UI(ID_FUNC_INFO, &CFunctionIndicatorDoc::OnUpdateFunctionInfo)
END_MESSAGE_MAP()


// CFunctionIndicatorDoc 构造/析构

CFunctionIndicatorDoc::CFunctionIndicatorDoc() noexcept
{
	this->m_ShowGrid = true;
	this->m_ShowAxis = true;
	this->m_ShowEdge = true;
	this->m_SingelMode = true;
	this->m_ShowFuncInfo = true;
	this->m_MinX = -10;
	this->m_MaxX = 10;
	this->m_MinY = -5;
	this->m_MaxY = 5;
	this->m_MoveMode = BAN;
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

void CFunctionIndicatorDoc::SetRange(double minX, double maxX, double minY, double maxY) {
	this->m_MinX = minX;
	this->m_MaxX = maxX;
	this->m_MinY = minY;
	this->m_MaxY = maxY;
}

//在图像移动时重新计算图像绘制点会使图像更为精准，但会导致一定程度的卡顿
//故暂时废弃，普通函数直接以定义域范围绘制图像，不用重新计算
void CFunctionIndicatorDoc::UpdateFunction() {
	//std::list<SML::MathFunction*>::iterator itFunc = this->m_FunctionList.begin();
	//std::list<DrawFuncData*>::iterator itDraw = this->m_DrawDataList.begin();

	////遍历函数链表
	//while (itFunc != this->m_FunctionList.end()) {
	//	
	//	//如果该函数为普通函数，重新计算当前图像绘制点
	//	if ((*itFunc)->GetType() == SML::Normal) {
	//		(*itDraw)->drawPoint = (*itFunc)->Calculate(this->m_MinX, this->m_MaxX, (*itDraw)->precision);
	//	}

	//	itFunc++;
	//	itDraw++;
	//}
}

void CFunctionIndicatorDoc::DelFunction(int num) {
	//序号超过范围，直接返回
	if (num <= 0 || num > this->m_FunctionList.size()) return;

	//遍历链表，搜索对应位置函数
	std::list<SML::MathFunction*>::iterator itFunc = this->m_FunctionList.begin();
	std::list<DrawFuncData*>::iterator itDraw = this->m_DrawDataList.begin();
	while ( num > 1 ) {
		itFunc++;
		itDraw++;
		num--;
	}

	//释放资源
	delete *itFunc;
	delete *itDraw;

	//删除链表结点
	this->m_FunctionList.erase(itFunc);
	this->m_DrawDataList.erase(itDraw);

}

void CFunctionIndicatorDoc::ClearFunction() {
	std::list<SML::MathFunction*>::iterator itFunc = this->m_FunctionList.begin();
	std::list<DrawFuncData*>::iterator itDraw = this->m_DrawDataList.begin();

	//遍历所有链表结点，并释放资源
	while (itFunc != this->m_FunctionList.end()) {
		delete* itFunc;
		delete* itDraw;
		itFunc++;
		itDraw++;
	}

	//链表清空
	this->m_FunctionList.clear();
	this->m_DrawDataList.clear();
}

MoveMode CFunctionIndicatorDoc::GetMoveMode() {
	return this->m_MoveMode;
}

void CFunctionIndicatorDoc::SetMoveMode(MoveMode mode) {
	this->m_MoveMode = mode;
}

bool CFunctionIndicatorDoc::IsShowEdge() {
	return this->m_ShowEdge;
}

bool CFunctionIndicatorDoc::IsShowAxis() {
	return this->m_ShowAxis;
}

bool CFunctionIndicatorDoc::IsShowGrid() {
	return this->m_ShowGrid;
}

bool CFunctionIndicatorDoc::IsShowFuncInfo() {
	return this->m_ShowFuncInfo;
}

// CFunctionIndicatorDoc 命令


void CFunctionIndicatorDoc::OnAddNormalFunc()
{
	//弹出增加普通函数窗口，并将当前X范围设置为函数定义域初始值
	CAddNormalFuncDlg dlg(this->m_MinX, this->m_MaxX);
	while (dlg.DoModal() == IDOK) {
		//获得函数类对象
		SML::MathFunction* pFunction = dlg.GetMathFunction();

		//新建绘画数据，传入必要参数
		DrawFuncData* dfd = new DrawFuncData;
		dfd->precision = dlg.GetPrecision();

		//计算函数图像数据，范围为X-Y轴显示范围，并将结果保存至绘画数据中
		//dfd->drawPoint = pFunction->Calculate(dlg.GetMin(), dlg.GetMax(), dfd->precision);
		//该方式虽然更为精准，但会导致图像移动时的卡顿，故直接采用下方以定义域范围绘制图像


		//计算函数图像数据，范围为该函数定义域，并将结果保存至绘画数据中
		//该方式与极坐标和参数方程的计算方式保持一致，图像移动会比较顺畅
		dfd->drawPoint = pFunction->Calculate(dlg.GetMin(), dlg.GetMax(), dfd->precision);

		//计算失败，弹出提示弹窗，释放相应资源并重新显示对话框
		if (pFunction->IsSuccess() == false) {
			AfxMessageBox(pFunction->GetError().c_str());
			delete pFunction;
			delete dfd;
			continue;
		}

		//将其他数据添加至绘画数据中
		dfd->expressionStr.push_back(CString("f(x)=") + dlg.GetExpressionStr());
		dfd->lineWidth = dlg.GetLineWidth();
		dfd->lineType = dlg.GetLineType();
		dfd->lineColor = dlg.GetLineColor();

		//将函数类对象和绘画数据添加至链表中保存
		this->m_FunctionList.push_back(pFunction);
		this->m_DrawDataList.push_back(dfd);

		break;
	}
	UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnAddPolarFunc()
{
	//弹出增加极坐标函数窗口，并将-pi~pi设置为函数定义域初始值
	CAddPolarFuncDlg dlg(-3.14, 3.14);
	while (dlg.DoModal() == IDOK) {
		//获得函数类对象
		SML::MathFunction* pFunction = dlg.GetMathFunction();

		//新建绘画数据，传入必要参数
		DrawFuncData* dfd = new DrawFuncData;
		dfd->precision = dlg.GetPrecision();

		//计算函数图像数据，范围为当前视图X轴范围，并将结果保存至绘画数据中
		//极坐标函数计算范围只局限在-pi到pi之间
		dfd->drawPoint = pFunction->Calculate(-PI, PI, dfd->precision);

		//计算失败，弹出提示弹窗，释放相应资源并重新显示对话框
		if (pFunction->IsSuccess() == false) {
			AfxMessageBox(pFunction->GetError().c_str());
			delete pFunction;
			delete dfd;
			continue;
		}

		//将其他数据添加至绘画数据中
		dfd->expressionStr.push_back(CString("r(a)=") + dlg.GetExpressionStr());
		dfd->lineWidth = dlg.GetLineWidth();
		dfd->lineType = dlg.GetLineType();
		dfd->lineColor = dlg.GetLineColor();

		//将函数类对象和绘画数据添加至链表中保存
		this->m_FunctionList.push_back(pFunction);
		this->m_DrawDataList.push_back(dfd);
		break;
	}
	UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnAddTwoFunc()
{
	//弹出增加参数方程函数窗口，并设置函数定义域初始值
	CAddTwoFuncDlg dlg(-5, 5);
	while (dlg.DoModal() == IDOK) {

		//获得函数类对象
		SML::MathFunction* pFunction = dlg.GetMathFunction();

		//新建绘画数据，传入必要参数
		DrawFuncData* dfd = new DrawFuncData;
		dfd->precision = dlg.GetPrecision();

		//计算函数图像数据，范围为该函数定义域，并将结果保存至绘画数据中
		dfd->drawPoint = pFunction->Calculate(dlg.GetMin(), dlg.GetMax(), dfd->precision);

		//计算失败，弹出提示弹窗，释放相应资源并重新显示对话框
		if (pFunction->IsSuccess() == false) {
			AfxMessageBox(pFunction->GetError().c_str());
			delete pFunction;
			delete dfd;
			continue;
		}

		//将其他数据添加至绘画数据中
		dfd->expressionStr.push_back(CString("x(t)=") + dlg.GetExpressionStrX());
		dfd->expressionStr.push_back(CString("y(t)=") + dlg.GetExpressionStrY());
		dfd->lineWidth = dlg.GetLineWidth();
		dfd->lineType = dlg.GetLineType();
		dfd->lineColor = dlg.GetLineColor();

		//将函数类对象和绘画数据添加至链表中保存
		this->m_FunctionList.push_back(pFunction);
		this->m_DrawDataList.push_back(dfd);
		break;
	}
	UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnDelFunc()
{
	CDelFuncDlg dlg;
	if (dlg.DoModal() == IDOK) {
		DelFunction(dlg.GetNum());  //删除函数
	}

	UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnDelAllFunc()
{
	this->ClearFunction(); //清空函数

	UpdateAllViews(NULL);

}


void CFunctionIndicatorDoc::OnSetXyRange()
{
	CSetXYRangeDlg dlg;
	while (dlg.DoModal() == IDOK ) {
		if (dlg.GetMinX() >= dlg.GetMaxX() || dlg.GetMinY() >= dlg.GetMaxY()) {
			AfxMessageBox("输入不合法，请检查！");
			continue;
		}
		this->SetRange(dlg.GetMinX(), dlg.GetMaxX(), dlg.GetMinY(), dlg.GetMaxY());
		break;
	}
	UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnEdge()
{
	this->m_ShowEdge = !this->m_ShowEdge;
	this->UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnAxis()
{
	this->m_ShowAxis = !this->m_ShowAxis;
	this->UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnGrid()
{
	this->m_ShowGrid = !this->m_ShowGrid;
	this->UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnUpdateEdge(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(this->m_ShowEdge);
}

void CFunctionIndicatorDoc::OnUpdateAxis(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(this->m_ShowAxis);
}


void CFunctionIndicatorDoc::OnUpdateGrid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(this->m_ShowGrid);
}



void CFunctionIndicatorDoc::OnMove()
{
	if (this->m_MoveMode == BAN) {
		this->m_MoveMode = MOVE;
	}
	else {
		this->m_MoveMode = BAN;
		::SetCursor(LoadCursor(NULL, IDC_HAND));
	}
}


void CFunctionIndicatorDoc::OnUpdateMove(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(this->m_MoveMode != BAN);
}


void CFunctionIndicatorDoc::OnFuncInfo()
{
	this->m_ShowFuncInfo = !this->m_ShowFuncInfo;
	this->UpdateAllViews(NULL);
}


void CFunctionIndicatorDoc::OnUpdateFunctionInfo(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(this->m_ShowFuncInfo);
}
