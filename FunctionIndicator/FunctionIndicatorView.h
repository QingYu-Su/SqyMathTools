
// FunctionIndicatorView.h: CFunctionIndicatorView 类的接口
//

#pragma once


class CFunctionIndicatorView : public CView
{
protected: // 仅从序列化创建
	CFunctionIndicatorView() noexcept;
	DECLARE_DYNCREATE(CFunctionIndicatorView)

// 特性
public:
	CFunctionIndicatorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CFunctionIndicatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	//在视图坐标系上绘制函数图像的区域坐标范围(真实坐标，非函数坐标)
	double m_Top, m_Bottom, m_Left, m_Right; 

private:
	//实现x轴上的数值在不同坐标系的转换，第二参数为转换模式
	//true-表示视图坐标系到函数坐标系的转换
	//false-表示函数坐标系到视图坐标系的转换
	double TransformX(double x, bool mode);

	//实现y轴上的数值在不同坐标系的转换，第二参数为转换模式
	//true-表示视图坐标系到函数坐标系的转换
	//false-表示函数坐标系到视图坐标系的转换
	double TransformY(double y, bool mode);

	void SetShowWindow(); //设置函数图像的有效绘画区域
	void DrawEdge(CDC* pDC);  //画绘画区域的边框
	void MarkCoordinateValue(CDC* pDC); //标注坐标系的各个坐标值
	void DrawGrid(CDC* pDC);  //画绘画区域内的网格
	void DrawAxis(CDC* pDC); //画绘画区域内的X-Y坐标轴

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FunctionIndicatorView.cpp 中的调试版本
inline CFunctionIndicatorDoc* CFunctionIndicatorView::GetDocument() const
   { return reinterpret_cast<CFunctionIndicatorDoc*>(m_pDocument); }
#endif

