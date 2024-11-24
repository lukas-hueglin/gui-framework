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

	Math::Point2D m_lastMousePos;
	Math::Point2D m_mouseDelta;

public:
	Widget(Window* p_parent);

	virtual void onTick(float deltaTime);

	virtual void onMouseHover(Math::Point2D point);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown(bool doubleClk, Math::Point2D point);
	virtual void onMouseRelease(Math::Point2D point);
	virtual void onMouseScroll(bool up, bool shift, bool ctr);

	virtual void onKeyDown(Key key);
	virtual void onKeyDown(char key);
};