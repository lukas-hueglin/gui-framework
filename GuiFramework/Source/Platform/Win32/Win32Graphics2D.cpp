#include "Gui.h"
#include "Platform/Win32/Win32Graphics2D.h"
#include "Platform/Win32/Win32Utils.h"

Win32Graphics2D::Win32Graphics2D(HWND hWnd) : m_hWnd(hWnd), mp2DFactory(nullptr), mpWriteFactory(nullptr), mpRenderTarget(nullptr) { }

Win32Graphics2D::~Win32Graphics2D() { }

void Win32Graphics2D::createGraphicsResources() {

    // Create D2D1 factory
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp2DFactory);

    // create DWrite factory
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(mpWriteFactory),
        reinterpret_cast<IUnknown**>(&mpWriteFactory)
    );
}

void Win32Graphics2D::initGraphicsResources() {

    HRESULT hr = S_OK;

    if (mpRenderTarget == nullptr) {

        // Get the window rectangle and size
        RECT rc;
        GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        // Create the render target
        hr = mp2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hWnd, size),
            &mpRenderTarget
        );

        // TODO: check hresult

        // enable DPI awareness
        SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }
}

void Win32Graphics2D::discardGraphicsResources() {

    Win32Utils::safeRelease(&mpRenderTarget);
    Win32Utils::safeRelease(&mpWriteFactory);
    Win32Utils::safeRelease(&mp2DFactory);
}

void Win32Graphics2D::drawLine(Math::Point2D& x, Math::Point2D& y, DrawStyle& style) {
}

void Win32Graphics2D::drawRectangle(Math::Rect& rect, DrawStyle& style) {
}

void Win32Graphics2D::drawText(std::wstring text) {
}
