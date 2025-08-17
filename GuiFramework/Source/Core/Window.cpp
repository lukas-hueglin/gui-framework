#include "Gui.h"
#include "Core/Window.h"

#include "Core/Graphics2D.h"

//#include "Widgets/Layout.h"
//#include "Widgets/DropDown.h"

//#include "Style/Style.h"

#include PLATFORM(WindowImpl.h)


Window::Window(const Credentials& creds, IApplication* p_app, std::wstring windowName) : Object(creds, p_app),
	m_windowName(windowName), mp_graphics(nullptr), /*mp_layout(nullptr), mp_dropDown(nullptr),*/
	m_rect(Math::Rect(0.f, 0.f, 0.f, 0.f)), m_layoutMouseHover(false), m_dropDownMouseHover(false) {

	INIT_IMPL_CLASS(*this)
}

Window::~Window() {
	delete &IMPL;
}

/*void Window::setLayout(Layout* p_layout) {

	mp_layout = p_layout;
	mp_layout->onResize(m_rect);
}*/

/*void Window::registerDropDown(DropDown* p_dropDown) {

	// remove old dropdown
	unregisterDropDown();

	// add new dropdown
	mp_dropDown = p_dropDown;
}*/

Graphics2D* Window::getGraphics() {

	return mp_graphics;
}

void Window::onTick(float deltaTime) {

	// begin painting
	if (mp_graphics) {
		mp_graphics->beginPaint();

		// update layout
		/*if (mp_layout != nullptr) {
			mp_layout->onTick(deltaTime);
		}

		// draw dropdown
		if (mp_dropDown != nullptr) {
			mp_dropDown->onPaint();
		}*/

		// end painting
		mp_graphics->endPaint();
	}
}

void Window::onInitialize() {

	IMPL.initialize(m_windowName);
}

void Window::onBegin() {

	if (mp_graphics)
		mp_graphics->createGraphicsAssets();

	// redraw all
	onResize(m_rect);
	onPaint();
}


void Window::onPaint() {

	// begin painting
	if (mp_graphics) {
		mp_graphics->beginPaint();

		// draw layout
		/*if (mp_layout != nullptr) {
			mp_layout->onPaint();
		}

		// draw dropdown
		if (mp_dropDown != nullptr) {
			mp_dropDown->onPaint();
		}*/

		// end painting
		mp_graphics->endPaint();
	}
}

void Window::onClose() {

	if (mp_graphics)
		mp_graphics->discardGraphicsAssets();
}

void Window::onResize(Math::Rect rect) {

	// update rect
	m_rect = rect;

	// resize canvas on graphics object
	if (mp_graphics)
		mp_graphics->resizeCanvas();

	// resize layout
	/*if (mp_layout != nullptr) {
		mp_layout->onResize(m_rect);
	}*/

	// delete dropdown if it exists
	//unregisterDropDown();
}

void Window::onMouseMove(Math::Point2D point) {

	// check if mouse hovers over dropdown
	/*if (mp_dropDown != nullptr && Math::pointInRect(mp_dropDown->getHitbox(), point)) {

		if (Math::pointInRect(mp_dropDown->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_dropDownMouseHover) {
				mp_dropDown->onMouseEnter();
				m_dropDownMouseHover = true;
				m_layoutMouseHover = false;
			}

			mp_dropDown->onMouseHover(point);
			return;
		}
		// check if mouse is registered as hovering
		else if (m_dropDownMouseHover) {
			mp_dropDown->onMouseLeave();
			m_dropDownMouseHover = false;
		}
	}

	// check if a layout exists
	if (mp_layout != nullptr) {

		if (Math::pointInRect(mp_layout->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_layoutMouseHover) {
				mp_layout->onMouseEnter();
				m_layoutMouseHover = true;
				m_dropDownMouseHover = false;
			}

			mp_layout->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (m_layoutMouseHover) {
			mp_layout->onMouseLeave();
			m_layoutMouseHover = false;
		}
	}*/
}

void Window::onMouseDown(bool doubleClk, Math::Point2D point) {

	// check if a layout exists
	/*if (mp_layout != nullptr) {

		// check if mouse hover over dropdown
		if (mp_dropDown != nullptr && Math::pointInRect(mp_dropDown->getHitbox(), point)) {
			mp_dropDown->onMouseDown(doubleClk, point);
		}

		// check if mouse hovers over layout
		else if (m_layoutMouseHover) {

			// delete dropdown if it exists
			unregisterDropDown();

			mp_layout->onMouseDown(doubleClk, point);
		}
	}*/
}

void Window::onMouseRelease(Math::Point2D point) {

	// check if a layout exists
	/*if (mp_layout != nullptr) {

		// check if mouse hovers over dropdown
		if (m_dropDownMouseHover) {
			mp_dropDown->onMouseRelease(point);
		}

		// check if mouse hovers over layout
		else if (m_layoutMouseHover) {
			mp_layout->onMouseRelease(point);
		}
	}*/
}

void Window::onMouseScroll(bool up, bool shift, bool ctr) {

	// check if a layout exists
	/*if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onMouseScroll(up, shift, ctr);
		}
	}*/
}

void Window::onKeyDown(Key key) {

	// check if a layout exists
	/*if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onKeyDown(key);
		}
	}*/
}

void Window::onKeyDown(char key) {

	// check if a layout exists
	/*if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onKeyDown(key);
		}
	}*/
}

/*void Window::unregisterDropDown() {

	if (mp_dropDown != nullptr) {
		delete mp_dropDown;
		mp_dropDown = nullptr;

		// repaint all
		onPaint();
	}
}*/
