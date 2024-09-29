#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

#include "Style/Style.h"

// define all types of Graphics to be used
template class IWindow<Graphics2D>;

// define all types that should be able to be created
template MainWindow<Graphics2D>* IWindow<Graphics2D>::create(std::wstring title);

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::IWindow() : mp_graphics(nullptr), m_rect(Math::Rect(0, 0, 0, 0)) { }

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::~IWindow() { }

template<class GRAPHICS_TYPE>
void IWindow<GRAPHICS_TYPE>::onBegin() {

	mp_graphics->createGraphicsResources();
}


void IWindow<Graphics2D>::onPaint() {

	// begin painting
	mp_graphics->beginPaint();

	// draw background
	mp_graphics->drawRectangle(m_rect, Style::Primary());

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
}


template<class GRAPHICS_TYPE>
template<class DERIVED_TYPE>
DERIVED_TYPE* IWindow<GRAPHICS_TYPE>::create(std::wstring title) {

	// create and initialize window
	DERIVED_TYPE* p_window = new DERIVED_TYPE;
	((IWindow<GRAPHICS_TYPE>*)p_window)->initialize(title);

	return p_window;
}
