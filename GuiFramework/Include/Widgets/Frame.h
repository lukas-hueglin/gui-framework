#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Common/WidgetUtils.h"
#include "Core/Object.h"


class GUI_API Frame : public Object {

protected:
	Window* mp_window;
	Frame* mp_parent;

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

// Win32 members
protected:
	// direct composition
	IDCompositionVisual* mp_dcompVisual;

public:
	Frame(const Credentials& creds, IApplication* p_app, Window* p_window, Frame* p_parent);
	~Frame();

	virtual void onBegin() override;

	virtual void onPaint();
	virtual void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point) = 0;
	virtual void onMouseEnter() = 0;
	virtual void onMouseLeave() = 0;
	virtual void onMouseDown(bool doubleClk, Math::Point2D point) = 0;
	virtual void onMouseRelease(Math::Point2D point) = 0;
	virtual void onMouseScroll(bool up, bool shift, bool ctr) = 0;

	virtual void onKeyDown(Key key) = 0;
	virtual void onKeyDown(char key) = 0;

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

	HRESULT initializeCompVisual(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice);
	HRESULT setContent(IDCompositionVisual* p_child);


	HRESULT updateVisalTransform();
	IDCompositionVisual* getVisual();


	friend class Window;
};