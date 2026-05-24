#pragma once
#include "Widgets/Widget2d.h"


class GUI_API Label : public Widget2d {

protected:
	std::wstring m_text;

// Win32 members
protected:
	ID2D1SolidColorBrush* mp_textBrush;
	IDWriteTextFormat* mp_textFormat;

public:
	Label(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, std::wstring text, WidgetStyle style = Style::Default());
	~Label();

	virtual void setText(std::wstring text);
	
protected:
	virtual HRESULT paintUI() override;
	virtual HRESULT initializeConsumables(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) override;
};