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
	Win32Utils::safeRelease(&mp_textLayout);
}

void Win32TextResource::initGraphicsAssets() {

    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
    IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

    if (p_renderTarget != nullptr && p_writeFactory != nullptr) {

        // Create brush
        p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_brush);
    }
}

void Win32TextResource::updateGraphicsAssets() {

    // get render target and write factory
    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
    IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

    if (p_renderTarget != nullptr && p_writeFactory != nullptr) {

        // delete old objects
        if (mp_textFormat != nullptr) {
            Win32Utils::safeRelease(&mp_textFormat);
        }
        if (mp_textLayout != nullptr) {
            Win32Utils::safeRelease(&mp_textLayout);
        }

        // create new text format
        p_writeFactory->CreateTextFormat(
            m_style.getFontName().c_str(),
            NULL,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            m_style.getFontSize(),
            L"en-us",
            &mp_textFormat
        );

        // create new text layout
        p_writeFactory->CreateTextLayout(
            m_text.c_str(),      // The string to be laid out and formatted.
            m_text.size(),  // The length of the string.
            mp_textFormat,  // The text format to apply to the string (contains font information, etc).
            m_rect.getWidth(),         // The width of the layout box.
            m_rect.getHeight(),        // The height of the layout box.
            &mp_textLayout  // The IDWriteTextLayout interface pointer.
        );

        // set alignment
        setTextAlignment(m_textAlignment);
    }
}

void Win32TextResource::drawText(std::wstring text, Math::Rect& rect, Alignment textAlignment) {

    // change variables
    setText(text); setRect(rect); setTextAlignment(textAlignment);

    // draw text
    drawText();
}

void Win32TextResource::drawText(std::wstring text) {

    // change variables
    setText(text);

    // draw text
    drawText();
}

void Win32TextResource::drawText() {

    if (mp_brush != nullptr && mp_textFormat != nullptr && mp_textLayout != nullptr) {

        // draw text
        mp_graphics->getRenderTarget()->DrawTextLayout(Win32Utils::D2D1Point(m_rect.topLeft()), mp_textLayout, mp_brush);
    }
    else {
        initGraphicsAssets();
        updateGraphicsAssets();
    }
}

void Win32TextResource::setText(std::wstring text) {

    m_text = text;
    updateGraphicsAssets();
}

void Win32TextResource::setRect(Math::Rect& rect) {

    m_rect = rect;

    if (mp_textLayout != nullptr) {
        mp_textLayout->SetMaxWidth(rect.getWidth());
        mp_textLayout->SetMaxHeight(rect.getHeight());
    }
}

void Win32TextResource::setTextAlignment(Alignment textAlignment) {

    m_textAlignment = textAlignment;
    
    // align text
    int horizontal_alignment = (3 - (textAlignment % 3)) % 3; // Left -> 0, Center -> 2, Right -> 1
    int vertical_alignment = (3 - (textAlignment / 3)) % 3; // Top -> 0, Center -> 2, Bottom -> 1

    if (mp_textLayout != nullptr) {
        mp_textLayout->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)horizontal_alignment);
        mp_textLayout->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)vertical_alignment);
    }
}

int Win32TextResource::getMousePosition(Math::Point2D point) {
    
    if (mp_textLayout != nullptr) {

        // create helper variables
        DWRITE_HIT_TEST_METRICS hitTestMetrics;
        BOOL isInside;
        BOOL isTrailing;

        // perform hit test
        mp_textLayout->HitTestPoint(point.x() - m_rect.left(), point.y() - m_rect.top(), &isTrailing, &isInside, &hitTestMetrics);

        return hitTestMetrics.textPosition;
    }

    return 0;
}

Math::Rect Win32TextResource::getCursorPosition(int cursor, bool trailing) {

    // create rect
    Math::Rect rect(0, 0, 0, 0);
    
    // create helper variables
    DWRITE_TEXT_METRICS textMetrics;
    DWRITE_HIT_TEST_METRICS hitTestMetrics;
    FLOAT pointX;
    FLOAT pointY;

    // get height of text
    mp_textLayout->GetMetrics(&textMetrics);

    // test first cursor
    mp_textLayout->HitTestTextPosition(cursor, trailing, &pointX, &pointY, &hitTestMetrics);
    rect.topLeft() = Math::Point2D(pointX, pointY) + m_rect.topLeft();
    rect.bottomRight() = Math::Point2D(pointX, pointY + textMetrics.height) + m_rect.topLeft();

    return rect;
}
