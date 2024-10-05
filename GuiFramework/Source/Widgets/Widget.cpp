#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window<Graphics2D>* p_parent) :
	mp_graphics(p_parent->getGraphics()),

	m_minSize(Math::Size(500, 100)),
	m_usedRect(Math::Rect(0, 0, 0, 0)),
	m_hitboxRect(Math::Rect(0, 0, 0, 0)),
	m_contentRect(Math::Rect(0, 0, 0, 0)),

	m_margin(0), m_padding(0),

	m_alignment(Alignment::Center),
	m_fillMode(FillMode::Shrink),

	m_mouseHover(false),
	m_mouseDown(false) {}

void Widget::onPaint() {}

void Widget::onResize(Math::Rect availableRect) {

	if (m_fillMode == FillMode::Expand) {

		m_usedRect = availableRect;

	}
	else {

		// if horizontal aligned left
		if (m_alignment % 3 == 0) {

			m_usedRect.left = availableRect.left;
			m_usedRect.right = m_usedRect.left + min(m_minSize.width, availableRect.getWidth());

		}

		// if horizontal aligned center
		if (m_alignment % 3 == 1) {

			// calculate integral sizes
			Math::Point2D center = availableRect.getCenter();
			float halfWidth = min(m_minSize.width, availableRect.getWidth()) / 2;

			m_usedRect.left = center.x - halfWidth;
			m_usedRect.right = center.x + halfWidth;

		}

		// if horizontal aligned right
		if (m_alignment % 3 == 2) {

			m_usedRect.right = availableRect.right;
			m_usedRect.left = m_usedRect.right - min(m_minSize.width, availableRect.getWidth());

		}

		// if vertical aligned top
		if (m_alignment / 3 == 0) {

			m_usedRect.top = availableRect.top;
			m_usedRect.bottom = m_usedRect.top + min(m_minSize.height, availableRect.getHeight());

		}

		// if vertical aligned center
		if (m_alignment / 3 == 1) {

			// calculate integral sizes
			Math::Point2D center = availableRect.getCenter();
			float halfHeight = min(m_minSize.height, availableRect.getHeight()) / 2;

			m_usedRect.top = center.y - halfHeight;
			m_usedRect.bottom = center.y + halfHeight;

		}

		// if vertical aligned bottom
		if (m_alignment / 3 == 2) {

			m_usedRect.bottom = availableRect.bottom;
			m_usedRect.top = m_usedRect.bottom - min(m_minSize.height, availableRect.getHeight());

		}
	}

	// calculate other rects
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::onMouseHover(Math::Point2D point) {

	// check for child hover

}

void Widget::onMouseEnter() {

	m_mouseHover = true;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseLeave() {

	m_mouseHover = false;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseDown() {

	// check for child click
	m_mouseDown = true;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseRelease() {

	// check for child release
	m_mouseDown = false;
	mp_graphics->scheduleRedraw();
}

float Widget::getMargin() {
	return m_margin;
}

float Widget::getPadding() {
	return m_padding;
}

Alignment Widget::getAlignment() {
	return m_alignment;
}

FillMode Widget::getFillMode() {
	return m_fillMode;
}

Math::Size Widget::getMinSize() {
	return m_minSize;
}

void Widget::setMargin(float margin) {

	m_margin = margin;

	// update hitbox and content rect
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::setPadding(float padding) {

	m_padding = padding;

	// update content rect
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::setAlignment(Alignment alignment) {
	
	m_alignment = alignment;
}

void Widget::setFillMode(FillMode fillMode) {

	m_fillMode = fillMode;
}

void Widget::setMinSize(Math::Size size) {

	m_minSize = size;
}

bool Widget::isMouseHovering() {

	return m_mouseHover;
}

Math::Rect Widget::getHitbox() {

	return m_hitboxRect;
}
