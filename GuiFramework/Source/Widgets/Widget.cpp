#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window<Graphics2D>* p_parent) :
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
	requestRedraw();
}

void Widget::onMouseDown() {

	m_mouseDown = true;
	requestRedraw();
}

void Widget::onMouseRelease() {

	m_mouseDown = false;
	requestRedraw();
}