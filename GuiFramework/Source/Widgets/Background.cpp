#include "Gui.h"
#include "Widgets/Background.h"

Background::Background(const Credentials& creds, IApplication* p_app, Window* p_window, Frame* p_parent, WidgetStyle style):
	Widget2d(creds, p_app, p_window, p_parent, style), mp_childFrame(nullptr), m_hoverChildFrame(false) {

	// override FillMode to Expand
	m_fillMode = FillMode::Expand;

	// override immediate mode
	enableImmediateMode();
}

Background::~Background() { }

void Background::onPaint() {
	Widget2d::onPaint();

	if (mp_childFrame != nullptr) {
		mp_childFrame->onPaint();
	}
}

void Background::onResize(Math::Rect availableRect) {
	Widget2d::onResize(availableRect);

	if (mp_childFrame != nullptr) {
		mp_childFrame->onResize(availableRect);
	}
}

void Background::onTick(float deltaTime) {
	Widget2d::onTick(deltaTime);

	if (mp_childFrame != nullptr) {
		if (mp_childFrame->isImmediateMode())
			mp_childFrame->onTick(deltaTime);
		if (mp_childFrame->hasRequestedRedraw())
			mp_childFrame->onPaint();
	}
}

void Background::onMouseEnter() {
	Widget2d::onMouseEnter();
}

void Background::onMouseLeave() {
	Widget2d::onMouseLeave();

	// make sure mouse left child frame
	if (m_hoverChildFrame && mp_childFrame != nullptr) {
		mp_childFrame->onMouseLeave();
		m_hoverChildFrame = false;
	}
}

void Background::onMouseHover(Math::Point2D point) {
	Widget2d::onMouseHover(point);

	// iterate over all frames
	if (mp_childFrame != nullptr) {

		if (Math::pointInRect(mp_childFrame->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_hoverChildFrame) {
				mp_childFrame->onMouseEnter();
				m_hoverChildFrame = true;
			}

			mp_childFrame->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (m_hoverChildFrame) {
			mp_childFrame->onMouseLeave();
			m_hoverChildFrame = false;
		}
	}
}

void Background::onMouseDown(bool doubleClk, Math::Point2D point) {
	Widget2d::onMouseDown(doubleClk, point);

	if (m_hoverChildFrame && mp_childFrame != nullptr) {
		mp_childFrame->onMouseDown(doubleClk, point);
	}
}

void Background::onMouseRelease(Math::Point2D point) {
	Widget2d::onMouseRelease(point);

	if (m_hoverChildFrame && mp_childFrame != nullptr) {
		mp_childFrame->onMouseRelease(point);
	}
}

void Background::onMouseScroll(bool up, bool shift, bool ctr) {
	Widget2d::onMouseScroll(up, shift, ctr);

	if (m_hoverChildFrame && mp_childFrame != nullptr) {
		mp_childFrame->onMouseScroll(up, shift, ctr);
	}
}

void Background::onKeyDown(Key key) {
	Widget2d::onKeyDown(key);

	if (m_hoverChildFrame && mp_childFrame != nullptr) {
		mp_childFrame->onKeyDown(key);
	}
}

void Background::onKeyDown(char key) {
	Widget2d::onKeyDown(key);

	if (m_hoverChildFrame && mp_childFrame != nullptr) {
		mp_childFrame->onKeyDown(key);
	}
}

void Background::setChildFrame(Frame* p_childFrame) {
	mp_childFrame = p_childFrame;
}

HRESULT Background::initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

	HRESULT hr;

	hr = Widget2d::initializeGraphicsResources(p_d3d11Device, p_dxgiDevice, p_d2d1Device, p_dcompDevice);

	if (SUCCEEDED(hr)) {
		hr = mp_childFrame->initializeGraphicsResources(p_d3d11Device, p_dxgiDevice, p_d2d1Device, p_dcompDevice);
	}

	return hr;
}
