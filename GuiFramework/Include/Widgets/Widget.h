#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Core/Graphics2D.h"
#include "Common/WidgetUtils.h"
#include "Widgets/Frame.h"


class GUI_API Widget : public Frame {
protected:
	bool m_mouseHover;
	bool m_mouseDown;

public:
	Widget(Window<Graphics2D>* p_parent);

	virtual void onTick(float deltaTime);

	virtual void onMouseHover(Math::Point2D point);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown(bool doubleClk);
	virtual void onMouseRelease();

	virtual void onKeyDown(Key key);
	virtual void onKeyDown(char key);
};