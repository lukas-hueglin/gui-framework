#include "Gui.h"
#include "Platform/Win32/Win32TextResource.h"
#include "Platform/Win32/Win32Utils.h"

Win32TextResource::Win32TextResource(Graphics2D* p_graphics, TextStyle style) : ITextResource(p_graphics, style) {

    initGraphicsAssets();
}

Win32TextResource::~Win32TextResource()
{
	Win32Utils::safeRelease(&mp_brush);
	Win32Utils::safeRelease(&mp_textFormat);
}

void Win32TextResource::initGraphicsAssets() {

    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
    IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

    if (p_renderTarget != nullptr && p_writeFactory != nullptr) {

        // Create brush
        p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_brush);

        // create text format
        p_writeFactory->CreateTextFormat(
            m_style.getFontName(),
            NULL,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            m_style.getFontSize(),
            L"en-us",
            &mp_textFormat
        );
    }
}

void Win32TextResource::drawText(const wchar_t* text, Math::Rect& rect, Alignment textAlignment) {

    if (mp_brush != nullptr && mp_textFormat != nullptr) {

        // align text
        int horizontal_alignment = (3 - (textAlignment % 3)) % 3; // Left -> 0, Center -> 2, Right -> 1
        int vertical_alignment = (3 - (textAlignment / 3)) % 3; // Top -> 0, Center -> 2, Bottom -> 1

        mp_textFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)horizontal_alignment);
        mp_textFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)vertical_alignment);

        // draw text
        mp_graphics->getRenderTarget()->DrawTextW(text, wcslen(text), mp_textFormat, Win32Utils::D2D1Rect(rect), mp_brush);
    }
    else {
        initGraphicsAssets();
    }
}

void Win32TextResource::setStyle(TextStyle style) {

}
