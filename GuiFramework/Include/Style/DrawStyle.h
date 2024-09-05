#pragma once
#include "Gui.h"
#include "Style/Color.h"

class DrawStyleBuilder;

class GUI_API DrawStyle {

private:
	Color m_edgeColor;
	Color m_fillColor;

	float m_edgeThickness;

private:
	DrawStyle();
public:
	~DrawStyle();

public:
	static DrawStyleBuilder create();

	Color& getEdgeColor();
	Color& getFillColor();
	float getEdgeThickness();

	friend class DrawStyleBuilder;
};