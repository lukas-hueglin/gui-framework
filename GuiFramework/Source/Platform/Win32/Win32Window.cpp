#include "Gui.h"
#include "Platform/Win32/Win32Window.h"

#include "Core/Graphics2D.h"

// define all used graphics types
template class Win32Window<Graphics2D>;


template<class GRAPHICS_TYPE>
Win32Window<GRAPHICS_TYPE>::Win32Window() : m_hWnd(NULL) { }

template<class GRAPHICS_TYPE>
Win32Window<GRAPHICS_TYPE>::~Win32Window() {

    DestroyWindow(m_hWnd);
}

template<class GRAPHICS_TYPE>
void Win32Window<GRAPHICS_TYPE>::initialize(std::wstring title) {

    // create win32 hWnd
    createHwnd(title.c_str(), WS_OVERLAPPEDWINDOW);
}

template<class GRAPHICS_TYPE>
void Win32Window<GRAPHICS_TYPE>::createHwnd(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu) {

    // create window class struct
    WNDCLASS wc = { 0 };

    // Check if class is already registered
    if (!GetClassInfo(HInstance(), getClassName(), &wc)) {

        // Register the window class.
        wc.lpfnWndProc = Win32Window::windowProc;
        wc.hInstance = HInstance();
        wc.lpszClassName = getClassName();

        RegisterClass(&wc);
    }

    // Create the window
    HWND hWnd = CreateWindowEx(
        dwExStyle,      // Extended window style
        getClassName(), // Window class
        lpWindowName,   // Window title
        dwStyle,        // Window style

        // Position and size
        x, y, nWidth, nHeight,

        hWndParent,     // Parent window
        hMenu,          // Menu
        HInstance(),    // Instance handle
        this            // Additional application data
    );
}

template<class GRAPHICS_TYPE>
LRESULT Win32Window<GRAPHICS_TYPE>::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    Win32Window* pThis = nullptr;

    // Check if window is created
    if (uMsg == WM_NCCREATE) {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (Win32Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

        // set window handle member variable
        pThis->m_hWnd = hWnd;

        // create graphics_type
        pThis->mp_graphics = new GRAPHICS_TYPE(hWnd);
    }
    else {

        // get window pointer from the userdata
        pThis = (Win32Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (pThis) {

        // filter out some messages and handle them here
        switch (uMsg) {


        default:
            // call the child function for handling the messages
            return pThis->handleMessage(uMsg, wParam, lParam);
        }

        
    }
    else {

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

template<class GRAPHICS_TYPE>
PCWSTR Win32Window<GRAPHICS_TYPE>::getClassName() {
    
    return L"Window";
}
