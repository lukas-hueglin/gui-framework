#pragma once
#include "Core/IGraphics.h"
#include "Common/MathUtils.h"
#include "Style/DrawStyle.h"

class GUI_API IGraphics2D : public IGraphics {

public:
	virtual void beginPaint() = 0;
	virtual void endPaint() = 0;

	virtual void drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle style) = 0;
	virtual void drawRectangle(Math::Rect& rect, DrawStyle style) = 0;

	virtual void drawText(std::wstring text /*, needs a text style */) = 0;

	virtual void scheduleRedraw() = 0;
};