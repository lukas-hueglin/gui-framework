#pragma once
#include "Core/IGraphics.h"
#include "Common/MathUtils.h"
#include "Style/DrawStyle.h"
#include "Style/TextStyle.h"

enum Alignment;

class GUI_API IGraphics2D : public IGraphics {

public:
	virtual void beginPaint() = 0;
	virtual void endPaint() = 0;

	virtual void drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle style) = 0;
	virtual void drawRectangle(Math::Rect& rect, DrawStyle style) = 0;

	virtual void drawText(const wchar_t* text, Math::Rect& rect, TextStyle style, Alignment textAlignment) = 0;
};