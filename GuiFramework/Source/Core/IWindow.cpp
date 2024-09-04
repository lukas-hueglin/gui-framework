#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/Window.h"
#include "Core/Graphics2D.h"

// define all types that should be able to be created
//template Window<Graphics2D>* IWindow<Window<Graphics2D>>::create();


template<class GRAPHICS_TYPE>
template<class DERIVED_TYPE>
DERIVED_TYPE* IWindow<GRAPHICS_TYPE>::create() {

	// create and initialize window
	DERIVED_TYPE* p_window = new DERIVED_TYPE;
	p_window->initialize();

	return p_window;
}
