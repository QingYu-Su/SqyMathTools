
// FunctionIndicatorDoc.h: CFunctionIndicatorDoc 类的接口
//


#pragma once
#include <list>
#include <string>
#include <vector>
#include "../SqyMathLibrary/include/MathFunction.h"
#pragma comment(lib, "../x64/Debug/SqyMathLibrary.lib")
namespace SML = SqyMathLibrary;  //命名空间重命名

//绘制所需的必要函数数据，简化Doc与View的数据传输，保证View只绘画而不计算
struct DrawFuncData { 
	std::vector<CString> expressionStr;  //函数表达式字符串，由于可能表达式不止一个，故用一个数组存放
	SML::FunctionMap drawPoint;  //函数绘制点
	size_t precision; //函数精细度
	int lineWidth;  //线宽
	int lineType;  //线型
	COLORREF lineColor;  //线颜色
};


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

public:
	double GetMinX();  //获得x范围最小值
	double GetMaxX();  //获得x范围最大值
	double GetMinY();  //获得y范围最小值
	double GetMaxY();  //获得y范围最大值
	std::list<DrawFuncData*> GetDrawDataList();  //获得绘制函数所需的所有数据

private:
	bool m_ShowGrid; //是否显示网格
	bool m_ShowAxis; //是否显示坐标轴
	bool m_ShowEdge; //是否显示边框
	bool m_SingelMode;   //单函数模式
	bool m_FixedXRange;	 //普通函数x范围是否固定，不固定的话随显示范围变化
	bool m_ShowPoint;//鼠标接近函数线时是否显示其坐标
	double m_MinX, m_MaxX; //当前x轴范围 
	double m_MinY, m_MaxY;//当前y轴范围

	//函数链表，保存了所有添加的函数以及一系列可供调用的方法
	std::list<SML::MathFunction*> m_FunctionList;

	//绘制函数数据链表，仅保存绘制图像所需要的必要数据，用来提供View绘图，与函数链表一一对应
	std::list<DrawFuncData*> m_DrawDataList;  
public:
	afx_msg void OnAddNormalFunc();
};
