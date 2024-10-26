#pragma once
#include "Gui.h"
#include "Core/Graphics2D.h"
#include "Common/MathUtils.h"
#include "Style/DrawStyle.h"


class GUI_API IGeometryResource {

protected:
	Graphics2D* mp_graphics;
	DrawStyle m_style;

public:
	IGeometryResource(Graphics2D* graphics, DrawStyle style);

public:
	virtual void drawLine(Math::Point2D& x, Math::Point2D& y) = 0;
	virtual void drawRectangle(Math::Rect& rect) = 0;

	virtual void setStyle(DrawStyle style) = 0;
};