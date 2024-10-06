#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window<Graphics2D>* p_parent) :
	Frame(p_parent),

	m_mouseHover(false),
	m_mouseDown(false) {}

void Widget::onMouseHover(Math::Point2D point) { }

void Widget::onMouseEnter() {

	m_mouseHover = true;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseLeave() {

	m_mouseHover = false;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseDown() {

	m_mouseDown = true;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseRelease() {

	m_mouseDown = false;
	mp_graphics->scheduleRedraw();
}