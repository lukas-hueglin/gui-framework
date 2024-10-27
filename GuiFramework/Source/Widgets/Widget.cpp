#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window* p_parent) :
	Frame(p_parent),

	m_mouseHover(false),
	m_mouseDown(false) {}

void Widget::onTick(float deltaTime) { }

void Widget::onMouseHover(Math::Point2D point) { }

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

void Widget::onKeyDown(Key key) { }

void Widget::onKeyDown(char key) { }
