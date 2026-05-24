#include "Gui.h"
#include "Widgets/Frame.h"
#include "Style/Style.h"
#include "Style/Palette.h"
#include "Common/Win32Utils.h"

Frame::Frame(const Credentials& creds, IApplication* p_app, Window* p_window, Frame* p_parent) :
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

	mp_dcompVisual(nullptr) {
}

Frame::~Frame() {

	Win32Utils::safeRelease(&mp_dcompVisual);
}

void Frame::onBegin() {
	
}

void Frame::onPaint() {

	m_requestRedraw = false;
}

void Frame::onResize(Math::Rect availableRect) {

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

	// calculate other rects
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);

	// update visual transform
	updateVisalTransform();
}

float Frame::getMargin() {

	return m_margin;
}

float Frame::getPadding() {

	return m_padding;
}

Math::Size Frame::getMinSize() {

	return m_minSize;
}

Alignment Frame::getAlignment() {

	return m_alignment;
}

FillMode Frame::getFillMode() {

	return m_fillMode;
}

void Frame::setMargin(float margin) {

	m_margin = margin;

	// update hitbox and content rect
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Frame::setPadding(float padding) {

	m_padding = padding;

	// update content rect
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Frame::setMinSize(Math::Size size) {

	m_minSize = size;
}

void Frame::setAlignment(Alignment alignment) {

	m_alignment = alignment;
}

void Frame::setFillMode(FillMode fillMode) {

	m_fillMode = fillMode;
}

Math::Rect Frame::getHitbox() {

	return m_hitboxRect;
}

bool Frame::hasRequestedRedraw() {

	return m_requestRedraw || m_immediateMode;
}

bool Frame::isImmediateMode() {
	return m_immediateMode;
}

void Frame::requestRedraw() {

	m_requestRedraw = true;
}

void Frame::enableImmediateMode() {

	m_immediateMode = true;
}

void Frame::disableImmediateMode() {

	m_immediateMode = false;
}

HRESULT Frame::initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

	return initializeCompVisual(p_dxgiDevice, p_d2d1Device, p_dcompDevice);
}

HRESULT Frame::initializeCompVisual(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

	// create direct composition visual
	HRESULT hr;

	hr = p_dcompDevice->CreateVisual(&mp_dcompVisual);

	if (SUCCEEDED(hr) && mp_parent != nullptr) {
		hr = mp_dcompVisual->AddVisual(mp_dcompVisual, FALSE, mp_parent->getVisual());
	}

	return hr;
}

HRESULT Frame::setContent(IDCompositionVisual* p_child) {
	return mp_dcompVisual->AddVisual(p_child, FALSE, mp_dcompVisual);
}

HRESULT Frame::updateVisalTransform() {

	HRESULT hr = mp_dcompVisual == nullptr ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		// create transformation matrix
		D2D_MATRIX_3X2_F transform = D2D1::Matrix3x2F::Translation(m_hitboxRect.left(), m_hitboxRect.top());
		
		// set visual transform
		hr = mp_dcompVisual->SetTransform(transform);
	}

	return hr;
}

IDCompositionVisual* Frame::getVisual() {
	return mp_dcompVisual;
}
