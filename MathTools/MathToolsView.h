
// MathToolsView.h: CMathToolsView 类的接口
//

#pragma once


class CMathToolsView : public CView
{
protected: // 仅从序列化创建
	CMathToolsView() noexcept;
	DECLARE_DYNCREATE(CMathToolsView)

// 特性
public:
	CMathToolsDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMathToolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MathToolsView.cpp 中的调试版本
inline CMathToolsDoc* CMathToolsView::GetDocument() const
   { return reinterpret_cast<CMathToolsDoc*>(m_pDocument); }
#endif

