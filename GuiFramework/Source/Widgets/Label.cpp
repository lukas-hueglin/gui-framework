#include "Gui.h"
#include "Widgets/Label.h"
#include "Style/Style.h"
#include "Style/Palette.h"
#include "Common/Win32Utils.h"

Label::Label(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, std::wstring text, WidgetStyle style):
    Widget2d(creds, p_app, p_window, p_parent, style),
    m_text(text),
    mp_textBrush(nullptr),
    mp_textFormat(nullptr) { }

Label::~Label() {
	Win32Utils::safeRelease(&mp_textFormat);
    Win32Utils::safeRelease(&mp_textBrush);
}

HRESULT Label::paintUI() {
    
    Widget2d::paintUI();

    // call perent
    HRESULT hr;
	hr = (mp_textBrush == nullptr) || (mp_textFormat == nullptr) ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		// draw text
		mp_d2d1DeviceContext->DrawTextW(m_text.c_str(), m_text.length(), mp_textFormat, Win32Utils::D2D1Rect(m_contentRect), mp_textBrush);
	}

	return hr;
}

HRESULT Label::initializeConsumables(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

    HRESULT hr;

    // call parent function
    hr = Widget2d::initializeConsumables(p_dxgiDevice, p_d2d1Device, p_dcompDevice);

    if (SUCCEEDED(hr)) {
        hr = mp_dwriteFactory == nullptr ? E_POINTER : hr;
    }

    if (SUCCEEDED(hr)) {
        // create new text format
        hr = mp_dwriteFactory->CreateTextFormat(
            m_style.getFontName().c_str(),
            NULL,
            (DWRITE_FONT_WEIGHT)m_style.getFontWeight(),
            (DWRITE_FONT_STYLE)m_style.getFontStyle(),
            DWRITE_FONT_STRETCH_NORMAL,
            m_style.getFontSize(),
            L"en-us",
            &mp_textFormat
        );
    }

    // align text
    int horizontal_alignment = (3 - (m_style.getTextAlignment() % 3)) % 3; // Left -> 0, Center -> 2, Right -> 1
    int vertical_alignment = (3 - (m_style.getTextAlignment() / 3)) % 3; // Top -> 0, Center -> 2, Bottom -> 1
    
    if (SUCCEEDED(hr)) {
        hr = mp_textFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)horizontal_alignment);
    }

    if (SUCCEEDED(hr)) {
        hr = mp_textFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)vertical_alignment);
    }

    if (SUCCEEDED(hr)) {
        // Create brush
        hr = mp_d2d1DeviceContext->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_textBrush);
    }

    return hr;
}

void Label::setText(std::wstring text) {

	m_text = text;
}
