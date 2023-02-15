
// FunctionIndicatorDoc.h: CFunctionIndicatorDoc 类的接口
//


#pragma once


class CFunctionIndicatorDoc : public CDocument
{
protected: // 仅从序列化创建
	CFunctionIndicatorDoc() noexcept;
	DECLARE_DYNCREATE(CFunctionIndicatorDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CFunctionIndicatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	bool m_ShowGrid; //是否显示网格
	bool m_ShowAxis; //是否显示坐标轴
	bool m_ShowEdge; //是否显示边框
	bool m_SingelMode;   //单函数模式
	bool m_FixedXRange;	 //普通函数x范围是否固定，不固定的话随显示范围变化
	bool m_ShowPoint;//鼠标接近函数线时是否显示其坐标
	double m_MinX, m_MaxX; //x轴显示范围 
	double m_MinY, m_MaxY;//y轴显示范围
public:
	afx_msg void OnAddNormalFunc();
};
