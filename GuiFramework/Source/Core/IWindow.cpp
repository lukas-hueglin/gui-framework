#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

#include "Widgets/Layout.h"

#include "Style/Style.h"

// define all types that should be able to be created
template MainWindow* IWindow::create(std::wstring title);

IWindow::IWindow() : mp_graphics(nullptr), mp_layout(nullptr), m_rect(Math::Rect(0.f, 0.f, 0.f, 0.f)), m_layoutMouseHover(false) { }

IWindow::~IWindow() {

	delete mp_backgroundResource;
}

void IWindow::setLayout(Layout* p_layout) {

	mp_layout = p_layout;
	mp_layout->onResize(m_rect);
}

Graphics2D* IWindow::getGraphics() {

	return mp_graphics;
}

void IWindow::onTick(float deltaTime) {

	// begin painting
	mp_graphics->beginPaint();

	// update layout
	if (mp_layout != nullptr) {
		mp_layout->onTick(deltaTime);
	}

	// end painting
	mp_graphics->endPaint();
}

void IWindow::onBegin() {

	mp_graphics->createGraphicsAssets();
}


void IWindow::onPaint() {

	// begin painting
	mp_graphics->beginPaint();

	if (mp_backgroundResource == nullptr) {
		// create geometry reesource
		mp_backgroundResource = new GeometryResource(mp_graphics, Style::Primary());
	}

	// draw background
	mp_backgroundResource->drawRectangle(m_rect);

	// draw layout
	if (mp_layout != nullptr) {
		mp_layout->onPaint();
	}

	// end painting
	mp_graphics->endPaint();
}

void IWindow::onDestroy() {

	mp_graphics->discardGraphicsAssets();
}

void IWindow::onResize(Math::Rect rect) {

	// update rect
	m_rect = rect;

	// resize canvas on graphics object
	mp_graphics->resizeCanvas();

	// resize layout
	if (mp_layout != nullptr) {
		mp_layout->onResize(m_rect);
	}
}

void IWindow::onMouseMove(Math::Point2D point) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		if (Math::pointInRect(mp_layout->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_layoutMouseHover) {
				mp_layout->onMouseEnter();
				m_layoutMouseHover = true;
			}

			mp_layout->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (m_layoutMouseHover) {
			mp_layout->onMouseLeave();
			m_layoutMouseHover = false;
		}
	}
}

void IWindow::onMouseDown(bool doubleClk, Math::Point2D point) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onMouseDown(doubleClk, point);
		}
	}
}

void IWindow::onMouseRelease(Math::Point2D point) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onMouseRelease(point);
		}
	}
}

void IWindow::onKeyDown(Key key) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onKeyDown(key);
		}
	}
}

void IWindow::onKeyDown(char key) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onKeyDown(key);
		}
	}
}


template<class DERIVED_TYPE>
DERIVED_TYPE* IWindow::create(std::wstring title) {

	// create and initialize window
	DERIVED_TYPE* p_window = new DERIVED_TYPE;
	((IWindow*)p_window)->initialize(title);

	return p_window;
}
