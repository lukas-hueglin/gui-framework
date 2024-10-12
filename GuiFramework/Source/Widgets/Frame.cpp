#include "Gui.h"
#include "Widgets/Frame.h"
#include "Style/Style.h"

Frame::Frame(Window<Graphics2D>* p_parent) :
	mp_graphics(p_parent->getGraphics()),

	m_minSize(Math::Size(500, 100)),
	m_usedRect(Math::Rect(0.f, 0.0f, 0.f, 0.f)),
	m_hitboxRect(Math::Rect(0.f, 0.f, 0.f, 0.f)),
	m_contentRect(Math::Rect(0.f, 0.f, 0.f, 0.f)),

	m_alignment(Alignment::Center),
	m_fillMode(FillMode::Shrink),

	m_margin(0), m_padding(0) {}


#ifdef DEBUG_UI
void Frame::onPaint() {
	mp_graphics->drawRectangle(m_usedRect, Style::Debug1());
	mp_graphics->drawRectangle(m_hitboxRect, Style::Debug2());
	mp_graphics->drawRectangle(m_contentRect, Style::Debug3());
}
#endif

void Frame::onResize(Math::Rect availableRect) {

	if (m_fillMode == FillMode::Expand) {

		m_usedRect = availableRect;

	}
	else {

		// if horizontal aligned left
		if (m_alignment % 3 == 0) {

			m_usedRect.left() = availableRect.left();
			m_usedRect.right() = m_usedRect.left() + min(m_minSize.width(), availableRect.getWidth());

		}

		// if horizontal aligned center
		if (m_alignment % 3 == 1) {

			// calculate integral sizes
			Math::Point2D center = availableRect.getCenter();
			float halfWidth = min(m_minSize.width(), availableRect.getWidth()) / 2;

			m_usedRect.left() = center.x() - halfWidth;
			m_usedRect.right() = center.x() + halfWidth;

		}

		// if horizontal aligned right
		if (m_alignment % 3 == 2) {

			m_usedRect.right() = availableRect.right();
			m_usedRect.left() = m_usedRect.right() - min(m_minSize.width(), availableRect.getWidth());

		}

		// if vertical aligned top
		if (m_alignment / 3 == 0) {

			m_usedRect.top() = availableRect.top();
			m_usedRect.bottom() = m_usedRect.top() + min(m_minSize.height(), availableRect.getHeight());

		}

		// if vertical aligned center
		if (m_alignment / 3 == 1) {

			// calculate integral sizes
			Math::Point2D center = availableRect.getCenter();
			float halfHeight = min(m_minSize.height(), availableRect.getHeight()) / 2;

			m_usedRect.top() = center.y() - halfHeight;
			m_usedRect.bottom() = center.y() + halfHeight;

		}

		// if vertical aligned bottom
		if (m_alignment / 3 == 2) {

			m_usedRect.bottom() = availableRect.bottom();
			m_usedRect.top() = m_usedRect.bottom() - min(m_minSize.height(), availableRect.getHeight());

		}
	}

	// calculate other rects
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

float Frame::getMargin() {

	return m_margin;
}

float Frame::getPadding() {

	return m_padding;
}

Math::Size Frame::getMinSize() {

	return m_minSize;
}

Alignment Frame::getAlignment() {

	return m_alignment;
}

FillMode Frame::getFillMode() {

	return m_fillMode;
}

void Frame::setMargin(float margin) {

	m_margin = margin;

	// update hitbox and content rect
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Frame::setPadding(float padding) {

	m_padding = padding;

	// update content rect
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Frame::setMinSize(Math::Size size) {

	m_minSize = size;
}

void Frame::setAlignment(Alignment alignment) {

	m_alignment = alignment;
}

void Frame::setFillMode(FillMode fillMode) {

	m_fillMode = fillMode;
}

Math::Rect Frame::getHitbox() {

	return m_hitboxRect;
}
