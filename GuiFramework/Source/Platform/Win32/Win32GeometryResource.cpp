#include "Gui.h"
#include "Platform/Win32/Win32GeometryResource.h"
#include "Platform/Win32/Win32Utils.h"

Win32GeometryResource::Win32GeometryResource(Graphics2D* p_graphics, DrawStyle style) : IGeometryResource(p_graphics, style) {

	initGraphicsAssets();
}

Win32GeometryResource::~Win32GeometryResource() {

	Win32Utils::safeRelease(&mp_fillBrush);
	Win32Utils::safeRelease(&mp_edgeBrush);
}

void Win32GeometryResource::initGraphicsAssets() {

	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		// Create fill and edge brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor()), &mp_fillBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getEdgeColor()), &mp_edgeBrush);
	}
}

void Win32GeometryResource::drawLine(Math::Point2D& a, Math::Point2D& b) {

	if (mp_edgeBrush != nullptr) {
		mp_graphics->getRenderTarget()->DrawLine(Win32Utils::D2D1Point(a), Win32Utils::D2D1Point(b), mp_edgeBrush, m_style.getEdgeThickness());
	}
}

void Win32GeometryResource::drawRectangle(Math::Rect& rect) {

	if (mp_fillBrush != nullptr && mp_edgeBrush != nullptr) {

		// get rendertarget
		ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

		// fill rectangle
		p_renderTarget->FillRectangle(Win32Utils::D2D1Rect(rect), mp_fillBrush);

		// draw edge
		p_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(rect), mp_edgeBrush);
	}
	else {
		initGraphicsAssets();
	}
}

void Win32GeometryResource::setStyle(DrawStyle style) {

	if (mp_fillBrush != nullptr && mp_edgeBrush != nullptr) {

		// set colors of brushes
		mp_fillBrush->SetColor(Win32Utils::D2D1Color(style.getFillColor()));
		mp_edgeBrush->SetColor(Win32Utils::D2D1Color(style.getEdgeColor()));
	}

	// change thickness
	m_style = style;
}
