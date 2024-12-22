#pragma once
#include "Gui.h"
#include "Style/Color.h"
#include "Style/LineStyle.h"
#include "Common/WidgetUtils.h"

class WidgetStyleBuilder;

class GUI_API WidgetStyle {

private:
	Color m_edgeColor;

	Color m_normalFillColor;
	Color m_hoverFillColor;
	Color m_clickFillColor;

	Color m_normalHighlightColor;
	Color m_hoverHighlightColor;
	Color m_clickHighlightColor;

	Color m_textColor;

	Alignment m_textAlignment;

	LineStyle m_lineStyle;

	std::wstring m_fontName;
	float m_fontSize;

	float m_edgeThickness;

	float m_topLeftRadius;
	float m_topRightRadius;
	float m_bottomLeftRadius;
	float m_bottomRightRadius;


private:
	WidgetStyle();

public:
	static WidgetStyleBuilder create();

	Color& getEdgeColor();
	Color& getFillColor(WidgetState state);
	Color& getHighlightColor(WidgetState state);
	Color& getTextColor();

	Alignment getTextAlignment();

	LineStyle getLineStyle();

	std::wstring getFontName();
	float getFontSize();

	float getEdgeThickness();

	float getTopLeftRadius();
	float getTopRightRadius();
	float getBottomLeftRadius();
	float getBottomRightRadius();

	friend class WidgetStyleBuilder;
};