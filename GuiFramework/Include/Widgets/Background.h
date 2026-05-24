#pragma once
#include "Widgets/Widget2d.h"

class GUI_API Background : public Widget2d {

protected:
	Frame* mp_childFrame;
	bool m_hoverChildFrame;

public:
	Background(const Credentials& creds, IApplication* p_app, Window* p_window, Frame* p_parent, WidgetStyle style = Style::Default());
	~Background();

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;
	void onTick(float deltaTime) override;

	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseHover(Math::Point2D point) override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onMouseRelease(Math::Point2D point) override;
	void onMouseScroll(bool up, bool shift, bool ctr) override;

	void onKeyDown(Key key) override;
	void onKeyDown(char key) override;

	void setChildFrame(Frame* p_childFrame);

protected:
	virtual HRESULT initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) override;
};