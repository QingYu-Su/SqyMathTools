
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

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FunctionIndicatorView.cpp 中的调试版本
inline CFunctionIndicatorDoc* CFunctionIndicatorView::GetDocument() const
   { return reinterpret_cast<CFunctionIndicatorDoc*>(m_pDocument); }
#endif

