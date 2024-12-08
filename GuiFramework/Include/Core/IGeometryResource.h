#pragma once
#include "Gui.h"
#include "Core/Graphics2D.h"
#include "Common/MathUtils.h"
#include "Style/DrawStyle.h"

#include <vector>


class GUI_API IGeometryResource {

protected:
	Graphics2D* mp_graphics;
	DrawStyle m_style;

public:
	IGeometryResource(Graphics2D* graphics, DrawStyle style);

public:
	virtual void drawLine(Math::Point2D& a, Math::Point2D& b) = 0;
	virtual void drawPolygon(std::vector<Math::Point2D>* p_points) = 0;
	virtual void drawArrow(Math::Point2D& a, Math::Point2D& b, float size) = 0;
	virtual void drawRectangle(Math::Rect& rect) = 0;

	virtual void setMask(Math::Rect& rect) = 0;
	virtual void releaseMask() = 0;

	virtual void setStyle(DrawStyle style) = 0;
};