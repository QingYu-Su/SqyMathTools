#include "CFunctionData.h"

CFunctionData::CFunctionData(SML::MathFunction* function, int penWidth, int penType, COLORREF penColor)
	:m_Function(function), m_PenWidth(penWidth), m_PenType(penType), m_PenColor(penColor)
{}

CFunctionData::~CFunctionData() {
	delete m_Function;
}