#pragma once
#include "Widgets/Layout.h"
#include <vector>

class GUI_API LinearLayout : public Layout {

protected:
	std::vector<Widget*> m_widgets;
	std::vector<float> m_weights;

private:
	Orientation m_orientation;

public:
	LinearLayout(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, Orientation orientation, WidgetStyle style = Style::Layout());

public:
	void onPaint() override;
	void onResize(Math::Rect availableRect) override;
	void onTick(float deltaTime) override;

	void onMouseHover(Math::Point2D point) override;

	void addWidget(Widget* p_widget, float weight = 1.0f);
	void removeWidget(Widget* p_widget);

private:
	void calcMinSize() override;

	// Win32 methods
protected:
	virtual HRESULT initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) override;
};