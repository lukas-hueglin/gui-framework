#include "Gui.h"
#include "Platform/Win32/Win32Graphics2D.h"
#include "Platform/Win32/Win32Utils.h"

Win32Graphics2D::Win32Graphics2D(HWND hWnd) : m_hWnd(hWnd), mp_2DFactory(nullptr), mp_writeFactory(nullptr), mp_renderTarget(nullptr) { }

Win32Graphics2D::~Win32Graphics2D() { }

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
        SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }
}

void Win32Graphics2D::discardGraphicsResources() {

    Win32Utils::safeRelease(&mp_renderTarget);
    Win32Utils::safeRelease(&mp_writeFactory);
    Win32Utils::safeRelease(&mp_2DFactory);
}

void Win32Graphics2D::drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle& style) {

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

void Win32Graphics2D::drawRectangle(Math::Rect& rect, DrawStyle& style) {

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

void Win32Graphics2D::drawText(std::wstring text) {

    // implement in future
}
