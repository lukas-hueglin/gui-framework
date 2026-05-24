#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"
#include "Common/Win32Utils.h"

Widget::Widget(const Credentials& creds, IApplication* p_app, Window* p_window, Frame* p_parent, WidgetStyle style) :
	Frame(creds, p_app, p_window, p_parent),

	m_id(0),
	m_mouseHover(false),
	m_mouseDown(false),
	m_lastMousePos(Math::Point2D(.0f, .0f)),
	m_mouseDelta(Math::Point2D(.0f, .0f)),
	m_style(style),

	mp_d3d11DeviceContext(nullptr),
	mp_dxgiSwapChain(nullptr) {}

Widget::~Widget() {
	Win32Utils::safeRelease(&mp_d3d11DeviceContext);
	Win32Utils::safeRelease(&mp_dxgiSwapChain);
}

void Widget::onResize(Math::Rect availableRect) {
    
    Frame::onResize(availableRect);

    // resize swapchain bitmap
    handleResize(m_hitboxRect.getWidth(), m_hitboxRect.getHeight());

    // paint
	handlePaint();
}

void Widget::onMouseHover(Math::Point2D point) {
	
	m_mouseDelta = m_lastMousePos - point;
	m_lastMousePos = point;
}

void Widget::onMouseEnter() {

	m_mouseHover = true;
	requestRedraw();
}

void Widget::onMouseLeave() {

	m_mouseHover = false;
	m_mouseDown = false;
	requestRedraw();
}

void Widget::onMouseDown(bool doubleClk, Math::Point2D point) {

	m_mouseDown = true;
	requestRedraw();
}

void Widget::onMouseRelease(Math::Point2D point) {

	m_mouseDown = false;
	requestRedraw();
}

void Widget::onMouseScroll(bool up, bool shift, bool ctr) { }

void Widget::onKeyDown(Key key) { }

void Widget::onKeyDown(char key) { }

void Widget::setId(int id) {

	m_id = id;
}

int Widget::getId() {

	return m_id;
}


HRESULT Widget::initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

    HRESULT hr;

    hr = Frame::initializeGraphicsResources(p_d3d11Device, p_dxgiDevice, p_d2d1Device, p_dcompDevice);

    if (SUCCEEDED(hr)) {
        hr = initializeCoreContexts(p_d3d11Device, p_dxgiDevice);
    }

    return hr;
}

HRESULT Widget::initializeCoreContexts(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice) {

    HRESULT hr = (p_d3d11Device == nullptr) || (p_dxgiDevice == nullptr) ? E_POINTER : S_OK;

    // create d3d11 device context
    if (SUCCEEDED(hr)) {
        hr = p_d3d11Device->CreateDeferredContext(0, &mp_d3d11DeviceContext);
    }

    // create dxgi adapter and factory
    IDXGIAdapter* p_dxgiAdapter = nullptr;
    if (SUCCEEDED(hr)) {
        hr = p_dxgiDevice->GetAdapter(&p_dxgiAdapter);
    }

    IDXGIFactory2* p_dxgiFactory = nullptr;
    if (SUCCEEDED(hr)) {
        hr = p_dxgiAdapter->GetParent(IID_PPV_ARGS(&p_dxgiFactory));
    }

    if (SUCCEEDED(hr)) {
        // create dxgi swap chain
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {
            m_hitboxRect.getWidth(),            // Width
            m_hitboxRect.getHeight(),           // Height
            DXGI_FORMAT_B8G8R8A8_UNORM,         // Format
            FALSE,                              // Stereo
            1,                                  // SampleDesc.Count
            0,                                  // SampleDesc.Quality
            DXGI_USAGE_RENDER_TARGET_OUTPUT,    // BufferUsage
            2,                                  // BufferCount
            DXGI_SCALING_STRETCH,               // Scaling
            DXGI_SWAP_EFFECT_FLIP_DISCARD,      // SwapEffect
            DXGI_ALPHA_MODE_PREMULTIPLIED       // AlphaMode
        };

        hr = p_dxgiFactory->CreateSwapChainForComposition(p_dxgiDevice, &swapChainDesc, nullptr, &mp_dxgiSwapChain);
    }

    if (SUCCEEDED(hr)) {
        hr = mp_dcompVisual->SetContent(mp_dxgiSwapChain);
    }

    // delete dxgi device, adapter and factory
    Win32Utils::safeRelease(&p_dxgiAdapter);
    Win32Utils::safeRelease(&p_dxgiFactory);

    return hr;
}