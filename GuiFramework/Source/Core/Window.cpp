#include "Gui.h"
#include "Core/Window.h"
#include "Core/IApplication.h"
#include "Common/Win32Utils.h"
#include "Widgets/Frame.h"

//#include "Widgets/Layout.h"
//#include "Widgets/DropDown.h"

//#include "Style/Style.h"
#include "Style/Palette.h"


Window::Window(const Credentials& creds, IApplication* p_app, std::wstring windowName) : Object(creds, p_app),
	m_windowName(windowName),
    mp_frame(nullptr),
    /* mp_dropDown(nullptr), */
	m_rect(Math::Rect(0.f, 0.f, 0.f, 0.f)),
    m_frameMouseHover(false),
    m_dropDownMouseHover(false),
	
    m_hWnd(nullptr),
    mp_d3d11Device(nullptr),
    mp_dxgiDevice(nullptr),
    mp_d2d1Device(nullptr),
    mp_dcompDevice(nullptr),
    mp_dcompTarget(nullptr) {
}

Window::~Window() {
	Win32Utils::safeRelease(&mp_d3d11Device);
	Win32Utils::safeRelease(&mp_dxgiDevice);

	Win32Utils::safeRelease(&mp_d2d1Device);

	Win32Utils::safeRelease(&mp_dcompDevice);
	Win32Utils::safeRelease(&mp_dcompTarget);
}

void Window::setFrame(Frame* p_frame) {

	mp_frame = p_frame;

	mp_frame->onResize(m_rect);
}

/*void Window::registerDropDown(DropDown* p_dropDown) {

	// remove old dropdown
	unregisterDropDown();

	// add new dropdown
	mp_dropDown = p_dropDown;
}*/

void Window::onTick(float deltaTime) {

	// update frame
	if (mp_frame != nullptr) {
		mp_frame->onTick(deltaTime);
	}

	// draw dropdown
	/*if (mp_dropDown != nullptr) {
		mp_dropDown->onPaint();
	}*/
}

void Window::onInitialize() {


    // create win32 hWnd
    // IMPORTANT: WS_EX_NOREDIRECTIONBITMAP ensures that no edge artefacts occur when resizing
    createHwnd(m_windowName.c_str(), WS_OVERLAPPEDWINDOW, WS_EX_NOREDIRECTIONBITMAP);



	handleUpdate();
}

void Window::onBegin() {


    // initialize graphics
    initializeGraphicsResources();

    // call on begin for frame
    if (mp_frame != nullptr) {
        mp_frame->onBegin();
    }

	onResize(m_rect);
	onPaint();

    // update graphics
    handleUpdate();
}


void Window::onPaint() {

	// draw frame
	if (mp_frame != nullptr) {
		mp_frame->onPaint();
	}

	// draw dropdown
	/*if (mp_dropDown != nullptr) {
		mp_dropDown->onPaint();
	}*/
    
    // update graphics
    handleUpdate();
}

void Window::onClose() { }

void Window::onResize(Math::Rect rect) {

	// update rect
	m_rect = rect;

	// resize frame
	if (mp_frame != nullptr) {
		mp_frame->onResize(m_rect);
	}

	// delete dropdown if it exists
	//unregisterDropDown();

    // update graphics
    handleUpdate();
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
	}*/

	// check if a frame exists
	if (mp_frame != nullptr) {

		if (Math::pointInRect(mp_frame->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_frameMouseHover) {
				mp_frame->onMouseEnter();
				m_frameMouseHover = true;
				m_dropDownMouseHover = false;
			}

			mp_frame->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (m_frameMouseHover) {
			mp_frame->onMouseLeave();
			m_frameMouseHover = false;
		}
	}
}

void Window::onMouseDown(bool doubleClk, Math::Point2D point) {

	// check if a frame exists
	if (mp_frame != nullptr) {

		// check if mouse hover over dropdown
		/*if (mp_dropDown != nullptr && Math::pointInRect(mp_dropDown->getHitbox(), point)) {
			mp_dropDown->onMouseDown(doubleClk, point);
		}*/

		// check if mouse hovers over frame
		/*else */ if (m_frameMouseHover) {

			// delete dropdown if it exists
			//unregisterDropDown();

			mp_frame->onMouseDown(doubleClk, point);
		}
	}
}

void Window::onMouseRelease(Math::Point2D point) {

	// check if a frame exists
	if (mp_frame != nullptr) {

		// check if mouse hovers over dropdown
		/*if (m_dropDownMouseHover) {
			mp_dropDown->onMouseRelease(point);
		}*/

		// check if mouse hovers over frame
		/*else*/ if (m_frameMouseHover) {
			mp_frame->onMouseRelease(point);
		}
	}
}

void Window::onMouseScroll(bool up, bool shift, bool ctr) {

	// check if a frame exists
	if (mp_frame != nullptr) {

		// check if mouse hovers over frame
		if (m_frameMouseHover) {
			mp_frame->onMouseScroll(up, shift, ctr);
		}
	}
}

void Window::onKeyDown(Key key) {

	// check if a frame exists
	if (mp_frame != nullptr) {

		// check if mouse hovers over frame
		if (m_frameMouseHover) {
			mp_frame->onKeyDown(key);
		}
	}
}

void Window::onKeyDown(char key) {

	// check if a frame exists
	if (mp_frame != nullptr) {

		// check if mouse hovers over frame
		if (m_frameMouseHover) {
			mp_frame->onKeyDown(key);
		}
	}
}

void Window::messageBox(const std::wstring& title, const std::wstring& text) {
    MessageBox(m_hWnd, text.c_str(), title.c_str(), MB_OK);
}

/*void Window::unregisterDropDown() {

	if (mp_dropDown != nullptr) {
		delete mp_dropDown;
		mp_dropDown = nullptr;

		// repaint all
		onPaint();
	}
}*/

HRESULT Window::createHwnd(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu) {

    // create window class struct
    WNDCLASS wc = { 0 };
    wc.style = CS_DBLCLKS;

    // Check if class is already registered
    if (!GetClassInfo(HInstance(), getClassName(), &wc)) {

        // Register the window class.
        wc.lpfnWndProc = Window::windowProc;
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

    return HRESULT_FROM_WIN32(GetLastError());
}

HRESULT Window::initializeGraphicsResources() {

    HRESULT hr = S_OK;

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // create the D3D11 device object. The D3D11_CREATE_DEVICE_BGRA_SUPPORT
    hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &mp_d3d11Device,
        nullptr,
        nullptr
    );

    // create dxgi device
    if (SUCCEEDED(hr)) {
        hr = mp_d3d11Device->QueryInterface(IID_PPV_ARGS(&mp_dxgiDevice));
    }

    // Create direct2d factory and device
    ID2D1Factory1* p_d2d1Factory = nullptr;
    if (SUCCEEDED(hr)) {
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &p_d2d1Factory);
    }

    if (SUCCEEDED(hr)) {
        hr = p_d2d1Factory->CreateDevice(mp_dxgiDevice, &mp_d2d1Device);
    }

    // create direct composition device and target
    if (SUCCEEDED(hr)) {
        hr = DCompositionCreateDevice(mp_dxgiDevice, IID_PPV_ARGS(&mp_dcompDevice));
    }

    if (SUCCEEDED(hr)) {
        hr = mp_dcompDevice->CreateTargetForHwnd(m_hWnd, TRUE, &mp_dcompTarget);
    }

    if (SUCCEEDED(hr) && mp_frame != nullptr) {
        hr = mp_frame->initializeGraphicsResources(mp_d3d11Device, mp_dxgiDevice, mp_d2d1Device, mp_dcompDevice);
    }

    if (SUCCEEDED(hr) && mp_frame != nullptr) {
        hr = setTargetRoot(mp_frame->getVisual());
    }

    // delete d2d1 factory
    Win32Utils::safeRelease(&p_d2d1Factory);

    return hr;
}

HRESULT Window::handleUpdate() {
    HRESULT hr = mp_dcompDevice == nullptr ? E_POINTER : S_OK;

    if (SUCCEEDED(hr)) {
        hr = mp_dcompDevice->Commit();
    }

    return hr;
}

HRESULT Window::setTargetRoot(IDCompositionVisual* p_visual) {

    HRESULT hr = mp_dcompTarget == nullptr ? E_POINTER : S_OK;

    if (SUCCEEDED(hr)) {
        hr = mp_dcompTarget->SetRoot(p_visual);
    }

    return hr;
}

LRESULT Window::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    Window* p_this = nullptr;

    // Check if window is created
    if (uMsg == WM_NCCREATE) {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_this = (Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)p_this);

        // set window handle member variable
        p_this->m_hWnd = hWnd;

        // show window
        ShowWindow(hWnd, 1);
    }
    else {

        // get window pointer from the userdata
        p_this = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (p_this) {

        // filter out some messages and handle them here
        switch (uMsg) {

        case WM_CREATE:
        {
            return 1;
        }
        case WM_NCDESTROY:
        {
            p_this->getApplication()->invokeWindowClose(p_this);;
            return 1;
        }
        case WM_PAINT:
        {
            p_this->onPaint();
            return 1;
        }
        case WM_SIZE:
        {
            RECT rc;
            GetClientRect(p_this->m_hWnd, &rc);
            //float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onResize(Math::Rect(0, rc.right, 0, rc.bottom));
            return 1;
        }
        case WM_MOUSEMOVE:
        {
            //float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseMove(Math::Point2D(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            return 1;
        }
        case WM_LBUTTONDBLCLK:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseDown(true, Math::Point2D(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            return 1;
        }
        case WM_LBUTTONDOWN:
        {
            //float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseDown(false, Math::Point2D(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            return 1;
        }
        case WM_LBUTTONUP:
        {
            //float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseRelease(Math::Point2D(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            return 1;
        }
        case WM_KEYDOWN:
        {
            Key key = Win32Utils::convertWin32Keys(wParam);
            if (key != Key::Empty) {
                p_this->onKeyDown(key);
            }
            return 1;
        }
        case WM_CHAR:
        {
            // if characters are printable
            if (wParam >= 0x20 && wParam <= 0x7E) {
                p_this->onKeyDown((char)wParam);
            }
            return 1;
        }
        case WM_MOUSEWHEEL:
        {
            // extract data
            float zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            int fwKeys = GET_KEYSTATE_WPARAM(wParam);

            p_this->onMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam) > 0, (fwKeys >> 2) & 1, (fwKeys >> 3) & 1);
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

LRESULT Window::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {

    return DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
}

PCWSTR Window::getClassName() {

    return L"Window";
}

