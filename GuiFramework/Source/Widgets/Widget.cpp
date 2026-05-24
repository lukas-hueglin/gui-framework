#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"
#include "Common/Win32Utils.h"

Widget::Widget(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, WidgetStyle style) :
    Object(creds, p_app),
    mp_window(p_window),
    mp_parent(p_parent),

    m_minSize(Math::Size(150, 50)),
    m_usedRect(Math::Rect(0.f, 0.0f, 0.f, 0.f)),
    m_hitboxRect(Math::Rect(0.f, 0.f, 0.f, 0.f)),
    m_contentRect(Math::Rect(0.f, 0.f, 0.f, 0.f)),

    m_alignment(Alignment::Center),
    m_fillMode(FillMode::Shrink),

    m_margin(0), m_padding(0),

    m_immediateMode(false),
    m_requestRedraw(true),

	m_id(0),
	m_mouseHover(false),
	m_mouseDown(false),
	m_lastMousePos(Math::Point2D(.0f, .0f)),
	m_mouseDelta(Math::Point2D(.0f, .0f)),
	m_style(style),

    mp_dcompVisual(nullptr),
	mp_d3d11DeviceContext(nullptr),
	mp_dxgiSwapChain(nullptr) {}

Widget::~Widget() {
    Win32Utils::safeRelease(&mp_dcompVisual);
	Win32Utils::safeRelease(&mp_d3d11DeviceContext);
	Win32Utils::safeRelease(&mp_dxgiSwapChain);
}

void Widget::onPaint() {

    m_requestRedraw = false;
}

void Widget::onResize(Math::Rect availableRect) {
    
	if (m_fillMode == FillMode::Expand) {

		m_usedRect = availableRect;
	}
	else {

		// if horizontal aligned left
		if (m_alignment % 3 == 0) {

			m_usedRect.left() = availableRect.left();
			m_usedRect.right() = m_usedRect.left() + min(m_minSize.width(), availableRect.getWidth());
		}

		// if horizontal aligned center
		if (m_alignment % 3 == 1) {

			// calculate integral sizes
			Math::Point2D center = availableRect.getCenter();
			float halfWidth = min(m_minSize.width(), availableRect.getWidth()) / 2;

			m_usedRect.left() = center.x() - halfWidth;
			m_usedRect.right() = center.x() + halfWidth;

		}

		// if horizontal aligned right
		if (m_alignment % 3 == 2) {

			m_usedRect.right() = availableRect.right();
			m_usedRect.left() = m_usedRect.right() - min(m_minSize.width(), availableRect.getWidth());

		}

		// if vertical aligned top
		if (m_alignment / 3 == 0) {

			m_usedRect.top() = availableRect.top();
			m_usedRect.bottom() = m_usedRect.top() + min(m_minSize.height(), availableRect.getHeight());

		}

		// if vertical aligned center
		if (m_alignment / 3 == 1) {

			// calculate integral sizes
			Math::Point2D center = availableRect.getCenter();
			float halfHeight = min(m_minSize.height(), availableRect.getHeight()) / 2;

			m_usedRect.top() = center.y() - halfHeight;
			m_usedRect.bottom() = center.y() + halfHeight;
		}

		// if vertical aligned bottom
		if (m_alignment / 3 == 2) {

			m_usedRect.bottom() = availableRect.bottom();
			m_usedRect.top() = m_usedRect.bottom() - min(m_minSize.height(), availableRect.getHeight());
		}
	}

	// move used rect by offset
	m_offset = m_usedRect.topLeft();
	m_usedRect.topLeft() = Math::Point2D();
	m_usedRect.bottomRight() -= m_offset;

	// calculate other rects
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);

	// update visual transform
	updateVisalTransform();

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


float Widget::getMargin() {

	return m_margin;
}

float Widget::getPadding() {

	return m_padding;
}

Math::Size Widget::getMinSize() {

	return m_minSize;
}

Alignment Widget::getAlignment() {

	return m_alignment;
}

FillMode Widget::getFillMode() {

	return m_fillMode;
}

void Widget::setMargin(float margin) {

	m_margin = margin;

	// update hitbox and content rect
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::setPadding(float padding) {

	m_padding = padding;

	// update content rect
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::setMinSize(Math::Size size) {

	m_minSize = size;
}

void Widget::setAlignment(Alignment alignment) {

	m_alignment = alignment;
}

void Widget::setFillMode(FillMode fillMode) {

	m_fillMode = fillMode;
}

Math::Rect Widget::getHitbox() {

	return m_hitboxRect;
}

bool Widget::hasRequestedRedraw() {

	return m_requestRedraw || m_immediateMode;
}

bool Widget::isImmediateMode() {
	return m_immediateMode;
}

void Widget::requestRedraw() {

	m_requestRedraw = true;
}

void Widget::enableImmediateMode() {

	m_immediateMode = true;
}

void Widget::disableImmediateMode() {

	m_immediateMode = false;
}


HRESULT Widget::initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

    HRESULT hr;

    hr = initializeCompVisual(p_dxgiDevice, p_d2d1Device, p_dcompDevice);

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


HRESULT Widget::initializeCompVisual(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

	// create direct composition visual
	HRESULT hr;

	hr = p_dcompDevice->CreateVisual(&mp_dcompVisual);

	if (SUCCEEDED(hr) && mp_parent != nullptr) {
		hr = mp_parent->getVisual()->AddVisual(mp_dcompVisual, TRUE, nullptr);
	}

	if (SUCCEEDED(hr)) {
		hr = updateVisalTransform();
	}

	return hr;
}

HRESULT Widget::updateVisalTransform() {

	HRESULT hr = mp_dcompVisual == nullptr ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		// create transformation matrix
		D2D_MATRIX_3X2_F transform = D2D1::Matrix3x2F::Translation(m_offset.x(), m_offset.y());

		// set visual transform
		hr = mp_dcompVisual->SetTransform(transform);
	}

	return hr;
}

IDCompositionVisual* Widget::getVisual() {
	return mp_dcompVisual;
}