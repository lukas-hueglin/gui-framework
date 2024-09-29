#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

#include "Widgets/Widget.h"

#include "Style/Style.h"

// define all types of Graphics to be used
template class IWindow<Graphics2D>;

// define all types that should be able to be created
template MainWindow<Graphics2D>* IWindow<Graphics2D>::create(const wchar_t* title);

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::IWindow() : mp_graphics(nullptr), mp_widget(nullptr), m_rect(Math::Rect(0, 0, 0, 0)) { }

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::~IWindow() { }

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::setWidget(Widget* p_widget) {

	mp_widget = p_widget;
	mp_widget->onResize(m_rect);
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

	// draw widget
	if (mp_widget != nullptr) {
		mp_widget->onPaint();
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

	// resize widget
	if (mp_widget != nullptr) {
		mp_widget->onResize(m_rect);
	}
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onMouseMove(Math::Point2D point) {

	// check if a widget exists
	if (mp_widget != nullptr) {

		if (Math::pointInRect(mp_widget->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!mp_widget->isMouseHovering()) {
				mp_widget->onMouseEnter();
			}

			mp_widget->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (mp_widget->isMouseHovering()) {
			mp_widget->onMouseLeave();
		}
	}
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onMouseDown() {

	// check if a widget exists
	if (mp_widget != nullptr) {

		// check if mouse hovers over widget
		if (mp_widget->isMouseHovering()) {
			mp_widget->onMouseDown();
		}
	}
}

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onMouseRelease() {

	// check if a widget exists
	if (mp_widget != nullptr) {

		// check if mouse hovers over widget
		if (mp_widget->isMouseHovering()) {
			mp_widget->onMouseRelease();
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
