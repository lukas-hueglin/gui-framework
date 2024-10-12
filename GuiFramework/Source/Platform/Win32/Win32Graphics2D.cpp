#include "Gui.h"
#include "Platform/Win32/Win32Graphics2D.h"
#include "Platform/Win32/Win32Utils.h"
#include "Widgets/Widget.h"

Win32Graphics2D::Win32Graphics2D(HWND hWnd) : m_hWnd(hWnd), mp_2DFactory(nullptr), mp_writeFactory(nullptr), mp_renderTarget(nullptr) { }

Win32Graphics2D::~Win32Graphics2D() { }

void Win32Graphics2D::beginPaint() {

    // initialize graphics resources
    initGraphicsResources();

    // begin painting
    BeginPaint(this->m_hWnd, &m_ps);
    mp_renderTarget->BeginDraw();
}

void Win32Graphics2D::endPaint() {

    // end painting
    mp_renderTarget->EndDraw();
    EndPaint(this->m_hWnd, &m_ps);
}

void Win32Graphics2D::createGraphicsResources() {

    // Create D2D1 factory
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_2DFactory);

    // create DWrite factory
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(mp_writeFactory),
        reinterpret_cast<IUnknown**>(&mp_writeFactory)
    );
}

void Win32Graphics2D::initGraphicsResources() {

    HRESULT hr = S_OK;

    if (mp_renderTarget == nullptr) {

        // Get the window rectangle and size
        RECT rc;
        GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        // Create the render target
        hr = mp_2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hWnd, size),
            &mp_renderTarget
        );

        // TODO: check hresult

        // enable DPI awareness
        //SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }
}

void Win32Graphics2D::discardGraphicsResources() {

    Win32Utils::safeRelease(&mp_renderTarget);
    Win32Utils::safeRelease(&mp_writeFactory);
    Win32Utils::safeRelease(&mp_2DFactory);
}

void Win32Graphics2D::resizeCanvas() {

    if (mp_renderTarget != nullptr) {

        // get the window rectangle and size
        RECT rc;
        GetClientRect(this->m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        mp_renderTarget->Resize(size);
        InvalidateRect(this->m_hWnd, NULL, FALSE);
    }
}

void Win32Graphics2D::drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle style) {

    // check if is is transparent
    if (style.getEdgeColor().a > 0.f) {

        // create brush
        HRESULT hr;
        ID2D1SolidColorBrush* p_brush;
        hr = mp_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(style.getEdgeColor()), &p_brush);

        // draw
        if (hr == S_OK) {
            mp_renderTarget->DrawLine(Win32Utils::D2D1Point(x), Win32Utils::D2D1Point(y), p_brush, style.getEdgeThickness());
        }

        // destroy brush
        Win32Utils::safeRelease(&p_brush);
    }
}

void Win32Graphics2D::drawRectangle(Math::Rect& rect, DrawStyle style) {

    // check if fill is transparent
    if (style.getFillColor().a > 0.f) {

        // create brush
        HRESULT hr;
        ID2D1SolidColorBrush* p_brush;
        hr = mp_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(style.getFillColor()), &p_brush);

        // draw
        if (hr == S_OK) {
            mp_renderTarget->FillRectangle(Win32Utils::D2D1Rect(rect), p_brush);
        }

        // destroy brush
        Win32Utils::safeRelease(&p_brush);
    }

    // check if edge is transparent
    if (style.getEdgeColor().a > 0.f) {

        // create brush
        HRESULT hr;
        ID2D1SolidColorBrush* p_brush;
        hr = mp_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(style.getEdgeColor()), &p_brush);

        // draw
        if (hr == S_OK) {
            mp_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(rect), p_brush, style.getEdgeThickness());
        }

        // destroy brush
        Win32Utils::safeRelease(&p_brush);
    }
}

void Win32Graphics2D::drawText(const wchar_t* text, Math::Rect& rect, TextStyle style, Alignment textAlignment) {

    // create hresult
    HRESULT hr;

    // create brush
    ID2D1SolidColorBrush* p_brush;
    hr = mp_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(style.getTextColor()), &p_brush);

    // create text format
    IDWriteTextFormat* p_textformat;
    hr |= mp_writeFactory->CreateTextFormat(
        style.getFontName(),
        NULL,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        style.getFontSize(),
        L"en-us",
        &p_textformat
    );

    // align text
    int horizontal_alignment = (3 - (textAlignment % 3)) % 3; // Left -> 0, Center -> 2, Right -> 1
    int vertical_alignment = (3 - (textAlignment / 3)) % 3; // Top -> 0, Center -> 2, Bottom -> 1

    p_textformat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT) horizontal_alignment);
    p_textformat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)vertical_alignment);


    if (hr == S_OK) {
        mp_renderTarget->DrawTextW(
            text,
            wcslen(text),
            p_textformat,
            Win32Utils::D2D1Rect(rect),
            p_brush
        );
    }

    // destroy brush and text format
    Win32Utils::safeRelease(&p_brush);
    Win32Utils::safeRelease(&p_textformat);
}