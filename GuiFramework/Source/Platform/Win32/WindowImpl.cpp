#include "Gui.h"
#include "Platform/Win32/WindowImpl.h"
#include "Platform/Win32/Win32Utils.h"
#include "Core/Graphics2D.h"
#include "Core/IApplication.h"

Window::Impl::Impl(Window& def) : DEF(def), m_hWnd(NULL) { }

Window::Impl::~Impl() { }

void Window::Impl::initialize(std::wstring windowName) {

    // create win32 hWnd
    createHwnd(windowName.c_str(), WS_OVERLAPPEDWINDOW);
}

void Window::Impl::createHwnd(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu) {

    // create window class struct
    WNDCLASS wc = { 0 };
    wc.style = CS_DBLCLKS;

    // Check if class is already registered
    if (!GetClassInfo(HInstance(), getClassName(), &wc)) {

        // Register the window class.
        wc.lpfnWndProc = Window::Impl::windowProc;
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

LRESULT Window::Impl::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    Window::Impl* p_this = nullptr;

    // Check if window is created
    if (uMsg == WM_NCCREATE) {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_this = (Window::Impl*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)p_this);

        // set window handle member variable
        p_this->m_hWnd = hWnd;

        // create graphics_type
        p_this->DEF.mp_graphics = new Graphics2D(hWnd);

        // show window
        ShowWindow(hWnd, 1);
    }
    else {

        // get window pointer from the userdata
        p_this = (Window::Impl*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (p_this) {

        // filter out some messages and handle them here
        switch (uMsg) {

        case WM_CREATE:
        {
            p_this->DEF.onBegin();
            return 1;
        }
        case WM_NCDESTROY:
        {
            p_this->DEF.getApplication()->invokeWindowClose(&p_this->DEF);
            return 1;
        }
        case WM_PAINT:
        {
            p_this->DEF.onPaint();
            return 1;
        }
        case WM_SIZE:
        {
            RECT rc;
            GetClientRect(p_this->m_hWnd, &rc);
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->DEF.onResize(Math::Rect(0, rc.right / dpiScale, 0, rc.bottom / dpiScale));
            return 1;
        }
        case WM_MOUSEMOVE:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->DEF.onMouseMove(Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_LBUTTONDBLCLK:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->DEF.onMouseDown(true, Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_LBUTTONDOWN:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->DEF.onMouseDown(false, Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_LBUTTONUP:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float) USER_DEFAULT_SCREEN_DPI);

            p_this->DEF.onMouseRelease(Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_KEYDOWN:
        {
            Key key = Win32Utils::convertWin32Keys(wParam);
            if (key != Key::Empty) {
                p_this->DEF.onKeyDown(key);
            }
            return 1;
        }
        case WM_CHAR:
        {
            // if characters are printable
            if (wParam >= 0x20 && wParam <= 0x7E) {
                p_this->DEF.onKeyDown((char)wParam);
            }
            return 1;
        }
        case WM_MOUSEWHEEL:
        {
            // extract data
            float zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            int fwKeys = GET_KEYSTATE_WPARAM(wParam);

            p_this->DEF.onMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam) > 0, (fwKeys >> 2) & 1, (fwKeys >> 3) & 1);
            return 1;
        }
        default:
            // call the child function for handling the messages
            return p_this->handleMessage(uMsg, wParam, lParam);
        }
    }
    else {

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

LRESULT Window::Impl::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    	
    return DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
}

PCWSTR Window::Impl::getClassName() {
    
    return L"Window";
}
