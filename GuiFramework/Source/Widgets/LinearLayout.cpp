#include "Gui.h"
#include "Widgets/LinearLayout.h"

LinearLayout::LinearLayout(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, Orientation orientation, WidgetStyle style) : Layout(creds, p_app, p_window, p_parent, style), m_orientation(orientation) { }

void LinearLayout::onPaint() {

	// call parent function
	Layout::onPaint();

	// iterate over all widgets
	for (Widget* w : m_widgets) {
		w->onPaint();
	}
}

void LinearLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// calculate the sum of all weights
	float sumExpandWeights = 0;

	for (int i = 0; i < m_widgets.size(); ++i) {

		if (m_widgets.at(i)->getFillMode() == FillMode::Expand) {
			sumExpandWeights += m_weights.at(i);
		}
	}

	// iterate over all widgets again and set their available space
	Math::Rect minRect(availableRect.getCenter().x() - m_minSize.width() / 2, availableRect.getCenter().x() + m_minSize.width() / 2,
		availableRect.getCenter().y() - m_minSize.height() / 2, availableRect.getCenter().y() + m_minSize.height() / 2);

	Math::Rect avRect = Math::maxRect(availableRect, minRect);

	// calculate space required for shrink widgets and space left for expanding widgets
	float spaceLeft = availableRect.getSize()[m_orientation] - m_minSize[m_orientation];

	// calculate integral sizes
	float expandSpan;
	float widgetSpan;

	// check if expanding widgets are present
	if (sumExpandWeights == 0) {

		// if not align the content
		avRect.topLeft()[m_orientation] += spaceLeft / 2 * (int)getJustification(m_alignment, m_orientation);
	}
	else {

		// if there are calculate the size of each one.
		expandSpan = spaceLeft / sumExpandWeights;
	}

	// iterate over all widgets and set their sizes
	for (int i = 0; i < m_widgets.size(); ++i) {

		widgetSpan = m_widgets.at(i)->getMinSize()[m_orientation];

		if (m_widgets.at(i)->getFillMode() == FillMode::Expand)
			widgetSpan += expandSpan * m_weights.at(i);
			

		// resize avRect
		avRect.bottomRight()[m_orientation] = avRect.topLeft()[m_orientation] + widgetSpan;

		// resize widget
		m_widgets.at(i)->onResize(avRect);

		// set left for next one
		avRect.topLeft()[m_orientation] = avRect.bottomRight()[m_orientation];
	}
	
}

void LinearLayout::onTick(float deltaTime) {

	// iterate over all widgets
	for (Widget* w : m_widgets) {
		if (w->isImmediateMode())
			w->onTick(deltaTime);
		if (w->hasRequestedRedraw())
			w->onPaint();
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

void LinearLayout::addWidget(Widget* p_widget, float weight) {

	m_widgets.push_back(p_widget);
	m_weights.push_back(weight);

	onResize(m_usedRect);
}

void LinearLayout::removeWidget(Widget* p_widget) {

	// find index
	int index = std::distance(m_widgets.begin(), std::find(m_widgets.begin(), m_widgets.end(), p_widget));

	m_widgets.erase(m_widgets.begin() + index);
	m_weights.erase(m_weights.begin() + index);
}

void LinearLayout::calcMinSize() {

	float width = 0.0f;
	float height = 0.0f;

	if (m_orientation == Orientation::Horizontal) {

		for (int i = 0; i < m_widgets.size(); ++i) {

			width += m_widgets.at(i)->getMinSize().width();
			height = max(height, m_widgets.at(i)->getMinSize().height());
		}
	}
	else {

		for (int i = 0; i < m_widgets.size(); ++i) {

			height += m_widgets.at(i)->getMinSize().height();
			width = max(width, m_widgets.at(i)->getMinSize().width());
		}
	}

	m_minSize = Math::Size(width, height);
}

HRESULT LinearLayout::initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {
	
	HRESULT hr;

	hr = Layout::initializeGraphicsResources(p_d3d11Device, p_dxgiDevice, p_d2d1Device, p_dcompDevice);

	for (Widget* w : m_widgets) {
		if (!SUCCEEDED(hr)) break;

		hr = w->initializeGraphicsResources(p_d3d11Device, p_dxgiDevice, p_d2d1Device, p_dcompDevice);

	}

	return hr;
}