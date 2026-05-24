#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Common/WidgetUtils.h"
#include "Core/Object.h"
#include "Style/WidgetStyle.h"
#include "Style/Style.h"


class GUI_API Widget : public Object {

protected:
	Window* mp_window;
	Widget* mp_parent;

	Math::Point2D m_offset;

	Math::Size m_minSize;
	Math::Rect m_usedRect;
	Math::Rect m_hitboxRect;
	Math::Rect m_contentRect;

	Alignment m_alignment;
	FillMode m_fillMode;

	float m_margin;
	float m_padding;

	bool m_immediateMode;
	bool m_requestRedraw;

	int m_id;

	bool m_mouseHover;
	bool m_mouseDown;

	Math::Point2D m_lastMousePos;
	Math::Point2D m_mouseDelta;

	WidgetStyle m_style;

// Win32 members
protected:
	// direct composition
	IDCompositionVisual* mp_dcompVisual;

	// underlying graphics infrastructure
	ID3D11DeviceContext* mp_d3d11DeviceContext;
	IDXGISwapChain1* mp_dxgiSwapChain;

public:
	Widget(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, WidgetStyle style = Style::Default());
	~Widget();

	virtual void onPaint();
	virtual void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown(bool doubleClk, Math::Point2D point);
	virtual void onMouseRelease(Math::Point2D point);
	virtual void onMouseScroll(bool up, bool shift, bool ctr);

	virtual void onKeyDown(Key key);
	virtual void onKeyDown(char key);

	void setId(int id);
	int getId();

public:
	float getMargin();
	float getPadding();
	virtual Math::Size getMinSize();
	Alignment getAlignment();
	FillMode getFillMode();

	void setMargin(float margin);
	void setPadding(float padding);
	void setMinSize(Math::Size size);
	void setAlignment(Alignment alignment);
	void setFillMode(FillMode fillMode);

	Math::Rect getHitbox();

	bool hasRequestedRedraw();
	bool isImmediateMode();

protected:
	void requestRedraw();
	void enableImmediateMode();
	void disableImmediateMode();

// Win32 methods
protected:

	virtual HRESULT initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice);

	HRESULT initializeCoreContexts(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice);
	HRESULT initializeCompVisual(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice);

	HRESULT updateVisalTransform();
	IDCompositionVisual* getVisual();

	virtual HRESULT handlePaint() = 0;
	virtual HRESULT handleResize(UINT width, UINT height) = 0;

	friend class Window;
	friend class LinearLayout;
};
