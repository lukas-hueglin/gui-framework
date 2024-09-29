#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window<Graphics2D>* p_parent) :
	mp_graphics(p_parent->getGraphics()),
	m_minSize(Math::Rect(0, 0, 0, 0)),
	m_usedSize(Math::Rect(0, 0, 0, 0)),
	m_alignment(Alignment::Center),
	m_fillMode(FillMode::Expand) {}

void Widget::onPaint() {

	// draw background
	Math::Rect background = Math::shrinkRect(m_usedSize, m_margin);
	mp_graphics->drawRectangle(background, Style::Highlight());
}

void Widget::onResize(Math::Rect availableRect) {

	m_usedSize = availableRect;
}

void Widget::setMargin(float margin) {

	m_margin = margin;
}

void Widget::setPadding(float padding) {

	m_padding = padding;
}
