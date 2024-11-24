#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window* p_parent) :
	Frame(p_parent),

	m_mouseHover(false),
	m_mouseDown(false),
	m_lastMousePos(Math::Point2D(.0f, .0f)),
	m_mouseDelta(Math::Point2D(.0f, .0f)) {}

void Widget::onTick(float deltaTime) { }

void Widget::onMouseHover(Math::Point2D point) {
	
	m_mouseDelta = m_lastMousePos - point;
	m_lastMousePos = point;
}

void Widget::onMouseEnter() {

	m_mouseHover = true;
	requestRedraw();
}

void Widget::onMouseLeave() {

	m_mouseHover = false;
	m_mouseDown = false;
	requestRedraw();
}

void Widget::onMouseDown(bool doubleClk, Math::Point2D point) {

	m_mouseDown = true;
	requestRedraw();
}

void Widget::onMouseRelease(Math::Point2D point) {

	m_mouseDown = false;
	requestRedraw();
}

void Widget::onMouseScroll(bool up, bool shift, bool ctr) { }

void Widget::onKeyDown(Key key) { }

void Widget::onKeyDown(char key) { }
