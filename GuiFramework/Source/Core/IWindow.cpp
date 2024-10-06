#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

#include "Widgets/Layout.h"

#include "Style/Style.h"

// define all types of Graphics to be used
template class IWindow<Graphics2D>;

// define all types that should be able to be created
template MainWindow<Graphics2D>* IWindow<Graphics2D>::create(const wchar_t* title);

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::IWindow() : mp_graphics(nullptr), mp_layout(nullptr), m_rect(Math::Rect(0, 0, 0, 0)), m_layoutMouseHover(false) { }

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::~IWindow() { }

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::setLayout(Layout* p_layout) {

	mp_layout = p_layout;
	mp_layout->onResize(m_rect);
}

template<class GRAPHICS_TYPE>
GRAPHICS_TYPE* IWindow<GRAPHICS_TYPE>::getGraphics() {

	return mp_graphics;
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onBegin() {

	mp_graphics->createGraphicsResources();
}


void IWindow<Graphics2D>::onPaint() {

	// begin painting
	mp_graphics->beginPaint();

	// draw background
	mp_graphics->drawRectangle(m_rect, Style::Primary());

	// draw layout
	if (mp_layout != nullptr) {
		mp_layout->onPaint();
	}

	// end painting
	mp_graphics->endPaint();
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onDestroy() {

	mp_graphics->discardGraphicsResources();
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onResize(Math::Rect rect) {

	// update rect
	m_rect = rect;

	// resize canvas on graphics object
	mp_graphics->resizeCanvas();

	// resize layout
	if (mp_layout != nullptr) {
		mp_layout->onResize(m_rect);
	}
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onMouseMove(Math::Point2D point) {

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

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onMouseDown() {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onMouseDown();
		}
	}
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onMouseRelease() {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onMouseRelease();
		}
	}
}


template<class GRAPHICS_TYPE>
template<class DERIVED_TYPE>
DERIVED_TYPE* IWindow<GRAPHICS_TYPE>::create(const wchar_t* title) {

	// create and initialize window
	DERIVED_TYPE* p_window = new DERIVED_TYPE;
	((IWindow<GRAPHICS_TYPE>*)p_window)->initialize(title);

	return p_window;
}
