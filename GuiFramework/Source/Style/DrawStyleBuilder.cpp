#include "Gui.h"
#include "Style/DrawStyleBuilder.h"
#include "Style/DrawStyle.h"


DrawStyleBuilder::DrawStyleBuilder(DrawStyle& drawStyle) : m_drawStyle(drawStyle) { }

DrawStyleBuilder& DrawStyleBuilder::edgeColor(const Color& edgeColor) {

	m_drawStyle.m_edgeColor = edgeColor;
	return *this;
}

DrawStyleBuilder& DrawStyleBuilder::fillColor(const Color& fillColor) {

	m_drawStyle.m_fillColor = fillColor;
	return *this;
}

DrawStyleBuilder& DrawStyleBuilder::lineStyle(const LineStyle lineStyle) {

	m_drawStyle.m_lineStyle = lineStyle;
	return *this;
}

DrawStyleBuilder& DrawStyleBuilder::edgeThickness(const float edgeThickness) {

	m_drawStyle.m_edgeThickness = edgeThickness;
	return *this;
}

DrawStyleBuilder::operator DrawStyle() {

	return this->m_drawStyle;
}
