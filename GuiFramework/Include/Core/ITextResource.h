#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/TextStyle.h"
#include "Common/Rect.h"
#include <string>

class GUI_API ITextResource {

protected:
	Graphics2D* mp_graphics;

	std::wstring m_text;
	TextStyle m_style;
	Math::Rect m_rect;
	Alignment m_textAlignment;

public:
	ITextResource(Graphics2D* p_graphics, TextStyle style);

public:
	virtual void drawText(std::wstring text, Math::Rect& rect, Alignment textAlignment) = 0;
	virtual void drawText(std::wstring text) = 0;
	virtual void drawText() = 0;

	virtual void setText(std::wstring text) = 0;
	virtual void setRect(Math::Rect& rect) = 0;
	virtual void setTextAlignment(Alignment textAlignment) = 0;

	virtual int getMousePosition(Math::Point2D point) = 0;
	virtual Math::Rect getCursorPosition(int cursor, bool trailing = false) = 0;
};