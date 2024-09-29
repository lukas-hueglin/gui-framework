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
void Win32Window<GRAPHICS_TYPE>::initialize(const wchar_t* title) {

    // create win32 hWnd
    createHwnd(title, WS_OVERLAPPEDWINDOW);
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

    Win32Window* p_this = nullptr;

    // Check if window is created
    if (uMsg == WM_NCCREATE) {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_this = (Win32Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)p_this);

        // set window handle member variable
        p_this->m_hWnd = hWnd;

        // create graphics_type
        p_this->mp_graphics = new GRAPHICS_TYPE(hWnd);

        // show window
        ShowWindow(hWnd, 1);
    }
    else {

        // get window pointer from the userdata
        p_this = (Win32Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (p_this) {

        // filter out some messages and handle them here
        switch (uMsg) {

        case WM_CREATE:

            p_this->onBegin();
            return 1;

        case WM_DESTROY:

            p_this->onDestroy();
            PostQuitMessage(0); // if any window is closed, the program will exit
            return 1;

        case WM_PAINT:

            p_this->onPaint();
            return 1;

        case WM_SIZE:

            RECT rc;
            GetClientRect(p_this->m_hWnd, &rc);
            p_this->onResize(Math::Rect(rc));
            return 1;

        case WM_MOUSEMOVE:

            p_this->onMouseMove(Math::Point2D(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            return 1;

        case WM_LBUTTONDOWN:

            p_this->onMouseDown();
            return 1;

        case WM_LBUTTONUP:

            p_this->onMouseRelease();
            return 1;

        default:
            // call the child function for handling the messages
            return p_this->handleMessage(uMsg, wParam, lParam);
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
