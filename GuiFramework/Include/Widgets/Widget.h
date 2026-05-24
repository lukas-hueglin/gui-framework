#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Common/WidgetUtils.h"
#include "Widgets/Frame.h"
#include "Style/WidgetStyle.h"
#include "Style/Style.h"


class GUI_API Widget : public Frame {

protected:
	int m_id;

	bool m_mouseHover;
	bool m_mouseDown;

	Math::Point2D m_lastMousePos;
	Math::Point2D m_mouseDelta;

	WidgetStyle m_style;

// Win32 members
protected:
	// underlying graphics infrastructure
	ID3D11DeviceContext* mp_d3d11DeviceContext;
	IDXGISwapChain1* mp_dxgiSwapChain;

public:
	Widget(const Credentials& creds, IApplication* p_app, Window* p_window, Frame* p_parent, WidgetStyle style = Style::Default());
	~Widget();

	virtual void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point) override;
	virtual void onMouseEnter() override;
	virtual void onMouseLeave() override;
	virtual void onMouseDown(bool doubleClk, Math::Point2D point) override;
	virtual void onMouseRelease(Math::Point2D point) override;
	virtual void onMouseScroll(bool up, bool shift, bool ctr) override;

	virtual void onKeyDown(Key key) override;
	virtual void onKeyDown(char key) override;

	void setId(int id);
	int getId();

// Win32 methods
protected:

	virtual HRESULT initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) override;
	HRESULT initializeCoreContexts(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice);

	virtual HRESULT handlePaint() = 0;
	virtual HRESULT handleResize(UINT width, UINT height) = 0;
};
