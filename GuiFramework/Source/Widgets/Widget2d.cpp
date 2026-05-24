#include "Gui.h"
#include "Widgets/Widget2d.h"
#include "Common/Win32Utils.h"
#include "Style/Color.h"
#include "Style/Palette.h"

Widget2d::Widget2d(const Credentials& creds, IApplication* p_app, Window* p_window, Widget* p_parent, WidgetStyle style):
	Widget(creds, p_app, p_window, p_parent, style),

	mp_d2d1DeviceContext(nullptr),
	mp_dwriteFactory(nullptr),
	mp_d2d1TargetBitmap(nullptr),
	mp_backgroundBrush(nullptr) { }

Widget2d::~Widget2d() {

	Win32Utils::safeRelease(&mp_d2d1DeviceContext);
	Win32Utils::safeRelease(&mp_dwriteFactory);
	Win32Utils::safeRelease(&mp_d2d1TargetBitmap);
	Win32Utils::safeRelease(&mp_backgroundBrush);
}

void Widget2d::onPaint() {
	// call perent function
	Widget::onPaint();

	HRESULT hr = mp_d2d1TargetBitmap == nullptr ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		hr = handlePaint();
	}
	else {
		initializeBitmap();
	}
}

HRESULT Widget2d::paintUI() {

	HRESULT hr = (mp_d2d1DeviceContext == nullptr) || (mp_backgroundBrush == nullptr) ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		mp_d2d1DeviceContext->Clear(Win32Utils::D2D1Color(Palette::Background()));
	}

	return hr;
}

HRESULT Widget2d::initializeConsumables(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

	// create background brush
	return mp_d2d1DeviceContext->CreateSolidColorBrush(Win32Utils::D2D1Color(Color::Transparent), &mp_backgroundBrush);;
}

HRESULT Widget2d::initializeBitmap() {

	HRESULT hr = mp_dxgiSwapChain == nullptr ? E_POINTER : S_OK;

	// get dxgi back buffer
	IDXGISurface* p_dxgiBackBuffer = nullptr;
	if (SUCCEEDED(hr)) {
		hr = mp_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&p_dxgiBackBuffer));
	}

	// create bitmap and bind to direct2d device context
	D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	if (SUCCEEDED(hr)) {
		hr = mp_d2d1DeviceContext->CreateBitmapFromDxgiSurface(p_dxgiBackBuffer, &bitmapProperties, &mp_d2d1TargetBitmap);
	}

	if (SUCCEEDED(hr)) {
		mp_d2d1DeviceContext->SetTarget(mp_d2d1TargetBitmap);
	}

	// delete dxgi surface
	Win32Utils::safeRelease(&p_dxgiBackBuffer);

	return hr;
}

HRESULT Widget2d::handlePaint() {

	HRESULT hr = (mp_d2d1DeviceContext == nullptr) || (mp_dxgiSwapChain == nullptr) ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		// begin painting
		mp_d2d1DeviceContext->BeginDraw();

		// paintUI
		hr = paintUI();
	}

	if (SUCCEEDED(hr)) {
		// end paint
		mp_d2d1DeviceContext->EndDraw();
	}

	if (SUCCEEDED(hr)) {
		// swap buffers
		mp_dxgiSwapChain->Present(1, 0);
	}

	return hr;
}

HRESULT Widget2d::handleResize(UINT width, UINT height) {

	HRESULT hr = (mp_dxgiSwapChain == nullptr) || (mp_d2d1DeviceContext == nullptr) || (mp_d2d1TargetBitmap == nullptr) || (mp_d3d11DeviceContext == nullptr) ? E_POINTER : S_OK;

	if (SUCCEEDED(hr)) {
		// IMPORTANT: completly unbind all resources
		mp_d2d1DeviceContext->SetTarget(nullptr);
		Win32Utils::safeRelease(&mp_d2d1TargetBitmap); // Does this work?
		mp_d3d11DeviceContext->Flush();

		// resize the buffer
		hr = mp_dxgiSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
	}

	// recreate resources
	if (SUCCEEDED(hr)) {
		hr = initializeBitmap();
	}

	// paint buffers
	if (SUCCEEDED(hr)) {
		hr = handlePaint();
	}

	return hr;
}

HRESULT Widget2d::initializeGraphicsResources(ID3D11Device* p_d3d11Device, IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {
	
	HRESULT hr;
	
	hr = Widget::initializeGraphicsResources(p_d3d11Device, p_dxgiDevice, p_d2d1Device, p_dcompDevice);

	if (SUCCEEDED(hr)) {
		hr = initialize2DContexts(p_dxgiDevice, p_d2d1Device, p_dcompDevice);
	}

	if (SUCCEEDED(hr)) {
		hr = initializeBitmap();
	}

	if (SUCCEEDED(hr)) {
		hr = initializeConsumables(p_dxgiDevice, p_d2d1Device, p_dcompDevice);
	}

	return hr;
}

HRESULT Widget2d::initialize2DContexts(IDXGIDevice* p_dxgiDevice, ID2D1Device* p_d2d1Device, IDCompositionDevice* p_dcompDevice) {

	HRESULT hr;

	// Create direct2d device context
	hr = p_d2d1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &mp_d2d1DeviceContext);

	// create DWrite factory
	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_dwriteFactory), reinterpret_cast<IUnknown**>(&mp_dwriteFactory));
	}

	return hr;
}


