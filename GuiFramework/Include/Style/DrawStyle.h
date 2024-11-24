#pragma once
#include "Gui.h"
#include "Style/Color.h"
#include "Style/LineStyle.h"

class DrawStyleBuilder;

class GUI_API DrawStyle {

private:
	Color m_edgeColor;
	Color m_fillColor;
	LineStyle m_lineStyle;

	float m_edgeThickness;

private:
	DrawStyle();
public:
	~DrawStyle();

public:
	static DrawStyleBuilder create();

	Color& getEdgeColor();
	Color& getFillColor();
	LineStyle getLineStyle();
	float getEdgeThickness();

	friend class DrawStyleBuilder;
};