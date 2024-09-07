#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/Window.h"
#include "Core/Graphics2D.h"

// define all types of Graphics to be used
template class IWindow<Graphics2D>;

// define all types that should be able to be created
template Window<Graphics2D>* IWindow<Graphics2D>::create(std::wstring title);

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::IWindow() : mp_graphics(nullptr) { }

template<class GRAPHICS_TYPE>
IWindow<GRAPHICS_TYPE>::~IWindow() { }


template<class GRAPHICS_TYPE>
template<class DERIVED_TYPE>
DERIVED_TYPE* IWindow<GRAPHICS_TYPE>::create(std::wstring title) {

	// create and initialize window
	DERIVED_TYPE* p_window = new DERIVED_TYPE;
	((IWindow<GRAPHICS_TYPE>*)p_window)->initialize(title);

	return p_window;
}
