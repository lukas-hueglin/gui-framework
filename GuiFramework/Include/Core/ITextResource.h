#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/TextStyle.h"


class GUI_API ITextResource {

protected:
	Graphics2D* mp_graphics;
	TextStyle m_style;

public:
	ITextResource(Graphics2D* p_graphics, TextStyle style);

public:
	virtual void drawText(const wchar_t* text, Math::Rect& rect, Alignment textAlignment) = 0;
};