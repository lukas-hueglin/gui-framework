#include "Gui.h"
#include "Widgets/LinearLayout.h"

LinearLayout::LinearLayout(Window<Graphics2D>* p_parent, Orientation orientation) : Widget(p_parent), m_orientation(orientation), m_mouseHoverWidget(nullptr) { }

void LinearLayout::onPaint() {

	// iterate over all widgets
	for (Widget* w : m_widgets) {
		w->onPaint();
	}
}

void LinearLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	// iterate over all widgets and get shrink size
	Math::Size sumSize = Math::Size(0, 0);
	float sumWeights = 0;

	for (int i = 0; i < m_widgets.size(); ++i) {
		
		if (m_widgets.at(i)->getFillMode() == FillMode::Expand) {

			sumWeights += m_weights.at(i);
		}
		else {

			sumSize = sumSize + m_widgets.at(i)->getMinSize();
		}
	}

	// iterate over all widgets again and set their available space
	Math::Rect available = m_contentRect;

	// check if horizontal or vertical orientation is set
	if (m_orientation == Orientation::Horizontal) {

		// calculate integral sizes
		float expandWidth = (available.getWidth() - sumSize.width) / sumWeights;

		for (int i = 0; i < m_widgets.size(); ++i) {

			if (m_widgets.at(i)->getFillMode() == FillMode::Expand) {

				available.right = available.left + expandWidth * m_weights.at(i);
			}
			else {

				available.right = available.left + m_widgets.at(i)->getMinSize().width;
			}

			// resize widget
			m_widgets.at(i)->onResize(available);

			// set left for next one
			available.left = available.right;
		}
	}
	else {
		// calculate integral sizes
		float expandHeight = (available.getHeight() - sumSize.height) / sumWeights;

		for (int i = 0; i < m_widgets.size(); ++i) {

			if (m_widgets.at(i)->getFillMode() == FillMode::Expand) {

				available.bottom = available.top + expandHeight * m_weights.at(i);
			}
			else {

				available.bottom = available.top + m_widgets.at(i)->getMinSize().height;
			}

			// resize widget
			m_widgets.at(i)->onResize(available);

			// set top for next one
			available.top = available.bottom;
		}
	}
	
}

void LinearLayout::onMouseHover(Math::Point2D point) {

	// iterate over all widgets
	for (Widget* w : m_widgets) {

		if (Math::pointInRect(w->getHitbox(), point)) {

			// check if mouse was already hovering
			if (w != m_mouseHoverWidget) {
				w->onMouseEnter();
				m_mouseHoverWidget = w;
			}

			w->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (w == m_mouseHoverWidget) {
			w->onMouseLeave();
			m_mouseHoverWidget = nullptr;
		}
	}
}

void LinearLayout::onMouseLeave() {

	// make sure mouse left child widget
	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseLeave();
		m_mouseHoverWidget = nullptr;
	}
}

void LinearLayout::onMouseDown() {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseDown();
	}
}

void LinearLayout::onMouseRelease() {

	if (m_mouseHoverWidget != nullptr) {
		m_mouseHoverWidget->onMouseRelease();
	}
}

void LinearLayout::addWidget(Widget* p_widget, float weight) {

	m_widgets.push_back(p_widget);
	m_weights.push_back(weight);

	// resize layout
	onResize(m_usedRect);
}

void LinearLayout::removeWidget(Widget* p_widget) {

	// find index
	int index = std::distance(m_widgets.begin(), std::find(m_widgets.begin(), m_widgets.end(), p_widget));

	m_widgets.erase(m_widgets.begin() + index);
	m_weights.erase(m_weights.begin() + index);
}
