
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

void CFunctionIndicatorView::SetShowWindow() {
	CRect rect;
	GetClientRect(&rect);//获得当前视图区坐标范围大小数据

	//本程序绘制的函数图像不占据整个视图区，在视图中间80%的区域绘制
	this->m_Top = rect.bottom * 0.1;  
	this->m_Bottom = rect.bottom * 0.9;
	this->m_Left = rect.right * 0.1;
	this->m_Right = rect.right * 0.9;
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


// CFunctionIndicatorView 绘图

void CFunctionIndicatorView::OnDraw(CDC* pDC)
{
	CFunctionIndicatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	double maxX = pDoc->GetMaxX();
	double minX = pDoc->GetMinX();
	double maxY = pDoc->GetMaxY();
	double minY = pDoc->GetMinY();

	this->SetShowWindow(); //绘画前必须设置绘画区域
	this->DrawEdge(pDC);
	this->MarkCoordinateValue(pDC);
	this->DrawGrid(pDC);
	this->DrawAxis(pDC);
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
