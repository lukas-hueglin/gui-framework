#include "Gui.h"
#include "Platform/Win32/Win32MainWindow.h"
#include "Platform/Win32/Win32Window.h"

// define all used graphics types
template class Win32MainWindow<Graphics2D>;

template<class GRAPHICS_TYPE>
Win32MainWindow<GRAPHICS_TYPE>* Win32MainWindow<GRAPHICS_TYPE>::create(std::wstring title) {
	
	return Win32Window<GRAPHICS_TYPE>::create<Win32MainWindow<GRAPHICS_TYPE>>(title);
}

template<class GRAPHICS_TYPE>
PCWSTR Win32MainWindow<GRAPHICS_TYPE>::getClassName() {

	return L"MainWindow";
}

template<class GRAPHICS_TYPE>
LRESULT Win32MainWindow<GRAPHICS_TYPE>::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {

		// add cases for custom functionality

	default:

		return DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
	}
}
