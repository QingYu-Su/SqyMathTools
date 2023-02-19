﻿
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
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

void CFunctionIndicatorView::SetShowWindow() {
	CRect rect;
	GetClientRect(&rect);//获得当前视图区坐标范围大小数据

	//本程序绘制的函数图像不占据整个视图区，在视图中间80%的区域绘制
	this->m_Top = rect.bottom * 0.1;  
	this->m_Bottom = rect.bottom * 0.9;
	this->m_Left = rect.right * 0.05;
	this->m_Right = rect.right * 0.8;
}

double CFunctionIndicatorView::TransformX(double x, bool mode) {
	CFunctionIndicatorDoc* pDoc = GetDocument();
	
	double maxX = pDoc->GetMaxX();
	double minX = pDoc->GetMinX();
	
	if (mode == true) {  //视图坐标系->函数坐标系
		double unit = (maxX - minX) / (this->m_Right - this->m_Left); //转换单元
		return minX + (x - this->m_Left) * unit;
	}
	else { //函数坐标系->视图坐标系
		double unit = (this->m_Right - this->m_Left) / (maxX - minX); //转换单元
		return this->m_Left + (x - minX) * unit;
	}
}

double CFunctionIndicatorView::TransformY(double y, bool mode) {
	CFunctionIndicatorDoc* pDoc = GetDocument();

	double maxY = pDoc->GetMaxY();
	double minY = pDoc->GetMinY();

	if (mode == true) {  //视图坐标系->函数坐标系
		double unit = (maxY - minY) / (this->m_Bottom - this->m_Top);  //转换单元
		return minY + (this->m_Bottom - y) * unit;
	}
	else {  //函数坐标系->视图坐标系
		double unit = (this->m_Bottom - this->m_Top) / (maxY - minY);  //转换单元
		return this->m_Bottom - (y - minY) * unit;
	}

}

void CFunctionIndicatorView::DrawEdge(CDC* pDC) {
	//沿着坐标范围绘制普通直线
	pDC->MoveTo(this->m_Left, this->m_Top);
	pDC->LineTo(this->m_Left, this->m_Bottom);
	pDC->LineTo(this->m_Right, this->m_Bottom);
	pDC->LineTo(this->m_Right, this->m_Top);
	pDC->LineTo(this->m_Left, this->m_Top);
}

void CFunctionIndicatorView::MarkCoordinateValue(CDC* pDC) {
	CFunctionIndicatorDoc* pDoc = GetDocument();

	double maxX = pDoc->GetMaxX();
	double minX = pDoc->GetMinX();
	double maxY = pDoc->GetMaxY();
	double minY = pDoc->GetMinY();

	//标注x坐标信息
	double xPoint;

	//标注间的单元距离
	//当x坐标值比较大时，文本的显示内容更长，为了得标注文本清晰可见，需要使各个标注的单元距离更长，标注分布更稀
	int xUnit = minX > 100 ? 100 : 50; 

	for (xPoint = this->m_Left; xPoint < this->m_Right; xPoint += xUnit ) { //每隔一个xUnit大小的像素标注一个坐标值
		//标注的显示区域
		CRect textRect(xPoint - (xUnit / 2), this->m_Bottom + 1, xPoint + (xUnit / 2), this->m_Bottom + 20);

		//设置标注文本内容，需要进行x坐标值转换，仅显示小数点后两位
		CString xInfo;
		xInfo.Format(_T("%.2f"), this->TransformX(xPoint, true));

		//绘制，单行,上下左右居中显示
		pDC->DrawText(xInfo, &textRect, DT_SINGLELINE | DT_CENTER);
		
	}

	//标注最后一个x坐标，与绘制框太远则不显示
	if (xPoint - this->m_Right <= (xUnit / 2) ) {
		CRect textRect(this->m_Right, this->m_Bottom + 1, this->m_Right + 50, this->m_Bottom + 20);
		CString xInfo;
		xInfo.Format(_T("%.2f"), maxX);
		pDC->DrawText(xInfo, &textRect, DT_SINGLELINE | DT_LEFT | DT_TOP);
	}


	//标注y坐标信息
	int yPoint;

	//y轴为横向绘制标注，故设置固定单元距离，不会影响文本内容显示
	for (yPoint = this->m_Bottom - 50; yPoint > this->m_Top; yPoint -= 50) {
		//标注的显示区域
		CRect textRect(this->m_Left - 200, yPoint - 10, this->m_Left - 3, yPoint + 10);

		//设置标注文本内容，需要进行y坐标值转换，仅显示小数点后两位
		CString yInfo;
		yInfo.Format(_T("%.2f"), this->TransformY(yPoint, true));
		
		//绘制，单行,靠右显示
		pDC->DrawText(yInfo, &textRect, DT_SINGLELINE | DT_RIGHT);
	}

	//标注最后一个y坐标，与绘制框太远则不显示
	if (this->m_Top - yPoint <= 25) {
		CRect textRect(this->m_Left - 200, this->m_Top - 10, this->m_Left - 3, this->m_Top + 10);
		CString yInfo;
		yInfo.Format(_T("%.2f"), maxY);
		pDC->DrawText(yInfo, &textRect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
	}
}

void CFunctionIndicatorView::DrawGrid(CDC* pDC) {
	CPen pen(PS_DOT, 1, RGB(100, 100, 100)); //创建笔，虚线，灰色      
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);

	//从左往右每隔50个像素点绘制一条垂直方向虚线
	for (double xPoint = this->m_Left + 50; xPoint < this->m_Right; xPoint += 50) {
		pDC->MoveTo(xPoint, this->m_Top);
		pDC->LineTo(xPoint, this->m_Bottom);
	}

	//从下至上每隔50个像素点绘制一条水平方向虚线
	for (double yPoint = this->m_Bottom - 50; yPoint > this->m_Top; yPoint -= 50) {
		pDC->MoveTo(this->m_Left, yPoint);
		pDC->LineTo(this->m_Right, yPoint);
	}

	pDC->SelectObject(pOldPen);
}


void CFunctionIndicatorView::DrawAxis(CDC* pDC) {
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0)); //创建笔，实线，黑色
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);

	//获得函数坐标系上的(0, 0)点在视图坐标系上的具体坐标
	int zeroX = this->TransformX(0, false);
	int zeroY = this->TransformY(0, false);

	//判断x,y轴是否在当前视图显示范围内
	bool showX = zeroY >= this->m_Top && zeroY <= this->m_Bottom;
	bool showY = zeroX >= this->m_Left && zeroX <= this->m_Right;
	
	//X轴绘制
	if (showX) {
		//绘制X轴线
		pDC->MoveTo(this->m_Left - 10, zeroY);
		pDC->LineTo(this->m_Right + 10, zeroY);

		//绘制X轴标注
		pDC->MoveTo(this->m_Right + 10, zeroY);
		pDC->LineTo(this->m_Right + 5, zeroY + 5);
		pDC->MoveTo(this->m_Right + 10, zeroY);
		pDC->LineTo(this->m_Right + 5, zeroY - 5);
		pDC->TextOutA(this->m_Right + 10, zeroY, _T("X轴"));
	}

	//Y轴绘制
	if (showY) {
		//绘制Y轴线
		pDC->MoveTo(zeroX, this->m_Bottom + 10);
		pDC->LineTo(zeroX, this->m_Top - 10);

		//绘制Y轴标注
		pDC->MoveTo(zeroX, this->m_Top - 10);
		pDC->LineTo(zeroX - 5, this->m_Top - 5);
		pDC->MoveTo(zeroX, this->m_Top - 10);
		pDC->LineTo(zeroX + 5, this->m_Top - 5);
		pDC->TextOutA(zeroX + 5, this->m_Top - 10, _T("Y轴"));
	}

	//X轴与Y轴均在显示范围内，需标注坐标原点
	if (showX && showY) {
		pDC->TextOutA(zeroX + 1, zeroY + 1, _T("O"));
	}

	pDC->SelectObject(pOldPen);
}

void CFunctionIndicatorView::DrawFunction(CDC* pDC) {
	CFunctionIndicatorDoc* pDoc = GetDocument();

	//获得绘制函数图像的必要数据
	double maxX = pDoc->GetMaxX();
	double minX = pDoc->GetMinX();
	double maxY = pDoc->GetMaxY();
	double minY = pDoc->GetMinY();
	std::list<DrawFuncData*> drawDataList = pDoc->GetDrawDataList();
	
	std::list<DrawFuncData*>::iterator it;  //遍历图像绘制数据链表
	for (it = drawDataList.begin(); it != drawDataList.end(); it++) {
		
		DrawFuncData* data = *it;  //获取图像数据
		CPen pen(data->lineType, data->lineWidth, data->lineColor);  //根据设置创建笔
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);

		bool move = true;  //移动布尔值，遇到连续点时需要绘制直线，不连续点时仅移动当前绘制点

		//遍历函数点
		for (int i = 0; i < data->drawPoint->size(); i++) {
			SML::FunctionPoint point = (*(data->drawPoint))[i];

			//函数点为无穷或超出当前坐标范围时不进行绘制
			if (point.first == INF || point.second == INF
				||point.first == -INF || point.second == -INF
				|| point.first < minX || point.first > maxX 
				|| point.second < minY || point.second > maxY) {
				move = true;  //遇到下个可标记点时不绘制直线，只移动当前绘制点
				continue;
			}

			//移动与绘制点间直线
			if (move) {
				//移动当前绘制点，坐标需要进行坐标系转换
				pDC->MoveTo(this->TransformX(point.first,false), this->TransformY(point.second, false));
				move = false;
			}
			else {
				//绘制点间直线
				pDC->LineTo(this->TransformX(point.first, false), this->TransformY(point.second, false));
			}
		}

		pDC->SelectObject(pOldPen);
	}

	
}

void CFunctionIndicatorView::ShowFuncExpression(CDC* pDC) {
	CFunctionIndicatorDoc* pDoc = GetDocument();

	//绘制边框和提醒文字
	pDC->TextOutA(this->m_Right + 125, this->m_Top - 30, "函数表达式");
	pDC->MoveTo(this->m_Right + 300, this->m_Top);
	pDC->LineTo(this->m_Right + 50, this->m_Top);
	pDC->LineTo(this->m_Right + 50, this->m_Bottom + 50);

	//获得绘制数据
	std::list<DrawFuncData*> drawDataList = pDoc->GetDrawDataList();

	int top = this->m_Top + 5; //开始标注函数表达式的起始点
	int order = 1;  //函数表达式的序号

	std::list<DrawFuncData*>::iterator it;  //遍历函数图像数据
	for (it = drawDataList.begin(); it != drawDataList.end(); it++, top += 5, order++) {
		DrawFuncData* data = *it;  //获取图像数据

		pDC->SetTextColor(data->lineColor);  //设置文本颜色

		CString orderStr;
		orderStr.Format("%d:", order); //序号
		pDC->TextOutA(this->m_Right + 60, top, orderStr);

		//标注该函数的函数表达式
		for (int j = 0; j < data->expressionStr.size(); j++, top += 20) {
			//标注函数表达式文本
			pDC->TextOutA(this->m_Right + 80, top, data->expressionStr[j]);
		}

		pDC->SetTextColor(RGB(0, 0, 0));  //还原文本颜色
		
		//标记分隔线
		pDC->MoveTo(this->m_Right + 300, top);
		pDC->LineTo(this->m_Right + 50, top);

	}
}

void CFunctionIndicatorView::AmplifyImage() {
	CFunctionIndicatorDoc* pDoc = GetDocument();
	double maxX = pDoc->GetMaxX();
	double minX = pDoc->GetMinX();
	double maxY = pDoc->GetMaxY();
	double minY = pDoc->GetMinY();
	
	double valueX = (maxX - minX) * 0.1;
	double valueY = (maxY - minY) * 0.1;

	pDoc->SetRange(minX + valueX, maxX - valueX, minY + valueY, maxY - valueY);
	pDoc->UpdateFunction();
	this->Invalidate();
	this->UpdateWindow();

}

void CFunctionIndicatorView::ShrinkImage() {
	CFunctionIndicatorDoc* pDoc = GetDocument();
	double maxX = pDoc->GetMaxX();
	double minX = pDoc->GetMinX();
	double maxY = pDoc->GetMaxY();
	double minY = pDoc->GetMinY();

	double valueX = (maxX - minX) * 0.1;
	double valueY = (maxY - minY) * 0.1;

	pDoc->SetRange(minX - valueX, maxX + valueX, minY - valueY, maxY + valueY);
	pDoc->UpdateFunction();
	this->Invalidate();
	this->UpdateWindow();
}


// CFunctionIndicatorView 绘图

void CFunctionIndicatorView::OnDraw(CDC* pDC)
{
	CFunctionIndicatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	this->SetShowWindow(); //绘画前必须设置绘画区域
	this->DrawEdge(pDC);
	this->MarkCoordinateValue(pDC);
	this->DrawGrid(pDC);
	this->DrawAxis(pDC);
	this->DrawFunction(pDC);
	ShowFuncExpression(pDC);
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


BOOL CFunctionIndicatorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	switch (zDelta)
	{
	case -120: //向后滚动滚轮
		this->ShrinkImage();  //缩小图像
		break;
	case 120:  //向前滚动滚轮
		this->AmplifyImage();  //放大图像
		break;
	default:
		break;
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CFunctionIndicatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFunctionIndicatorDoc* pDoc = GetDocument();
	SetCapture();
	if (pDoc->GetMoveMode() == MOVE) {
		pDoc->SetMoveMode(MOVING);
		this->m_MoveStart.point = point;
		this->m_MoveStart.maxX = pDoc->GetMaxX();
		this->m_MoveStart.minX = pDoc->GetMinX();
		this->m_MoveStart.maxY = pDoc->GetMaxY();
		this->m_MoveStart.minY = pDoc->GetMinY();
		::SetCursor(LoadCursor(NULL, IDC_SIZEALL));
	}

	CView::OnLButtonDown(nFlags, point);
}


void CFunctionIndicatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CFunctionIndicatorDoc* pDoc = GetDocument();
	if (pDoc->GetMoveMode() == MOVING) {
		pDoc->SetMoveMode(MOVE);
		::SetCursor(LoadCursor(NULL, IDC_HAND));

		double valueX = this->TransformX(point.x, true) - this->TransformX(this->m_MoveStart.point.x, true);
		double valueY = this->TransformY(point.y, true) - this->TransformY(this->m_MoveStart.point.y, true);

		pDoc->SetRange(this->m_MoveStart.minX - valueX, this->m_MoveStart.maxX - valueX,
			this->m_MoveStart.minY - valueY, this->m_MoveStart.maxY - valueY);
		pDoc->UpdateFunction();
		this->Invalidate();
		this->UpdateWindow();
	}
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void CFunctionIndicatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CFunctionIndicatorDoc* pDoc = GetDocument();

	if (pDoc->GetMoveMode() == MOVING) {
		::SetCursor(LoadCursor(NULL, IDC_SIZEALL));

		double valueX = this->TransformX(point.x, true) - this->TransformX(this->m_MoveStart.point.x, true);
		double valueY = this->TransformY(point.y, true) - this->TransformY(this->m_MoveStart.point.y, true);

		pDoc->SetRange(this->m_MoveStart.minX - valueX, this->m_MoveStart.maxX - valueX,
			this->m_MoveStart.minY - valueY, this->m_MoveStart.maxY - valueY);

		pDoc->UpdateFunction();

		CDC* pDC = GetDC();
		//创建一个内存中的显示设备
		CDC MemDC;
		MemDC.CreateCompatibleDC(NULL);
		//创建一个内存中的图像
		CBitmap MemBitmap;
		CRect rect;
		GetClientRect(&rect);
		MemBitmap.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
		//指定内存显示设备在内存中的图像上画图
		MemDC.SelectObject(&MemBitmap);
		//先用一种颜色作为内存显示设备的背景色
		MemDC.FillSolidRect(rect.left, rect.top, rect.right, rect.bottom, RGB(144, 144, 144));
		this->OnDraw(&MemDC);
		//将内存中画好的图像直接拷贝到屏幕指定区域上
		pDC->BitBlt(rect.left, rect.top, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);

		//释放相关资源
		ReleaseDC(pDC);
	}
	
	if (pDoc->GetMoveMode() == MOVE) {
		::SetCursor(LoadCursor(NULL, IDC_HAND));
	}

	CView::OnMouseMove(nFlags, point);
}
