#pragma once
#include "Gui.h"
#include "Widgets/Widget.h"


class GUI_API Widget2d : public Widget {

private:
	bool m_drawBackground;

// Win32 members
protected:
	// direct 2d
	ID2D1DeviceContext* mp_d2d1DeviceContext;
	ID2D1Bitmap1* mp_d2d1TargetBitmap;

	// direct write
	IDWriteFactory* mp_dwriteFactory;

	// consumables
	ID2D1SolidColorBrush* mp_backgroundBrush;

#ifdef DEBUG_UI
	ID2D1SolidColorBrush* mp_usedBrush;
	ID2D1SolidColorBrush* mp_hitboxBrush;
	ID2D1SolidColorBrush* mp_contentBrush;
	ID2D1SolidColorBrush* mp_textBrush;
	bool m_tickFlip;
#endif // DEBUG_UI

public:
	Widget2d(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, WidgetStyle style = Style::Default());
	~Widget2d();
public:
	virtual void onPaint() override;

	void setDrawBackground(bool drawBackground);
	bool getDrawBackground() const;

// Win32 methods
protected:
	virtual HRESULT paintUI();

	virtual HRESULT initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) override;
	HRESULT initialize2DContexts(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice);
	virtual HRESULT initializeConsumables(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice);

	virtual HRESULT initializeBitmap();

	virtual HRESULT handlePaint() override;
	virtual HRESULT handleResize(UINT width, UINT height) override;
};