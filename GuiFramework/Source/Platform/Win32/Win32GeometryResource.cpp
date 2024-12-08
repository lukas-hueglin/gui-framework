#include "Gui.h"
#include "Platform/Win32/Win32GeometryResource.h"
#include "Platform/Win32/Win32Utils.h"

Win32GeometryResource::Win32GeometryResource(Graphics2D* p_graphics, DrawStyle style) : IGeometryResource(p_graphics, style) {

	initGraphicsAssets();
}

Win32GeometryResource::~Win32GeometryResource() {

	Win32Utils::safeRelease(&mp_fillBrush);
	Win32Utils::safeRelease(&mp_edgeBrush);
	Win32Utils::safeRelease(&mp_strokeStyle);
}

void Win32GeometryResource::initGraphicsAssets() {

	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_renderTarget != nullptr) {

		// Create fill and edge brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor()), &mp_fillBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getEdgeColor()), &mp_edgeBrush);
	}

	if (p_2DFactory != nullptr) {

		// create stroke style
		p_2DFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties(
				D2D1_CAP_STYLE_FLAT,
				D2D1_CAP_STYLE_FLAT,
				D2D1_CAP_STYLE_ROUND,
				D2D1_LINE_JOIN_MITER,
				10.0f,
				(D2D1_DASH_STYLE) m_style.getLineStyle(),
				0.0f
			),
			NULL,
			0,
			&mp_strokeStyle
		);
	}
}

void Win32GeometryResource::drawLine(Math::Point2D& a, Math::Point2D& b) {

	if (mp_edgeBrush != nullptr) {
		mp_graphics->getRenderTarget()->DrawLine(Win32Utils::D2D1Point(a), Win32Utils::D2D1Point(b), mp_edgeBrush, m_style.getEdgeThickness(), mp_strokeStyle);
	}
	else {
		initGraphicsAssets();
	}
}

void Win32GeometryResource::drawPolygon(std::vector<Math::Point2D> * p_points) {

	// get 2d factory
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	// create triangle
	ID2D1GeometrySink* p_sink;
	ID2D1PathGeometry* p_pathGeometry;
	HRESULT hr;

	if (p_2DFactory != nullptr) {

		// Create path geometry
		hr = p_2DFactory->CreatePathGeometry(&p_pathGeometry);

		if (SUCCEEDED(hr)) {

			// Write to the path geometry using the geometry sink.
			hr = p_pathGeometry->Open(&p_sink);

			if (SUCCEEDED(hr)) {

				// begin figure
				p_sink->BeginFigure(
					Win32Utils::D2D1Point(p_points->at(0)),
					D2D1_FIGURE_BEGIN_FILLED
				);

				// add all points
				for (Math::Point2D& point : (*p_points)) {
					p_sink->AddLine(Win32Utils::D2D1Point(point));
				}

				// end figure
				p_sink->EndFigure(D2D1_FIGURE_END_OPEN);

				hr = p_sink->Close();
			}
		}

		// draw 
		ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

		if (mp_edgeBrush != nullptr && p_renderTarget != nullptr) {

			p_renderTarget->DrawGeometry(p_pathGeometry, mp_edgeBrush);
		}
		else {
			initGraphicsAssets();
		}

		// delete resources
		Win32Utils::safeRelease(&p_sink);
		Win32Utils::safeRelease(&p_pathGeometry);
	}
}

void Win32GeometryResource::drawArrow(Math::Point2D& a, Math::Point2D& b, float size) {

	// calculate arrow head
	Math::Point2D base = b - a;
	base = base / base.length() * size;

	// calculate corners
	Math::Point2D c = b - base + Math::Point2D(-base.y(), base.x())/2;
	Math::Point2D d = b - base + Math::Point2D(base.y(), -base.x())/2;

	// get 2d factory
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	// create triangle
	ID2D1GeometrySink* p_sink;
	ID2D1PathGeometry* p_pathGeometry;
	HRESULT hr;

	if (p_2DFactory != nullptr) {

		hr = p_2DFactory->CreatePathGeometry(&p_pathGeometry);

		if (SUCCEEDED(hr))
		{
			// Write to the path geometry using the geometry sink.
			hr = p_pathGeometry->Open(&p_sink);

			if (SUCCEEDED(hr))
			{
				p_sink->BeginFigure(
					Win32Utils::D2D1Point(b),
					D2D1_FIGURE_BEGIN_FILLED
				);

				p_sink->AddLine(Win32Utils::D2D1Point(c));
				p_sink->AddLine(Win32Utils::D2D1Point(d));

				p_sink->EndFigure(D2D1_FIGURE_END_CLOSED);

				hr = p_sink->Close();
			}

		}

		// draw 
		ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

		if (mp_edgeBrush != nullptr && p_renderTarget != nullptr) {

			p_renderTarget->DrawLine(Win32Utils::D2D1Point(a), Win32Utils::D2D1Point(b), mp_edgeBrush, m_style.getEdgeThickness(), mp_strokeStyle);
			p_renderTarget->FillGeometry(p_pathGeometry, mp_fillBrush);
		}
		else {
			initGraphicsAssets();
		}

		// delete resources
		Win32Utils::safeRelease(&p_sink);
		Win32Utils::safeRelease(&p_pathGeometry);
	}
}

void Win32GeometryResource::drawRectangle(Math::Rect& rect) {

	if (mp_fillBrush != nullptr && mp_edgeBrush != nullptr) {

		// get rendertarget
		ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

		// fill rectangle
		p_renderTarget->FillRectangle(Win32Utils::D2D1Rect(rect), mp_fillBrush);

		// draw edge
		p_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(rect), mp_edgeBrush, m_style.getEdgeThickness(), mp_strokeStyle);
	}
	else {
		initGraphicsAssets();
	}
}

void Win32GeometryResource::setMask(Math::Rect& rect) {

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if(p_renderTarget != nullptr) {
		p_renderTarget->PushAxisAlignedClip(
			Win32Utils::D2D1Rect(rect),
			D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
		);

	}
}

void Win32GeometryResource::releaseMask() {

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {
		p_renderTarget->PopAxisAlignedClip();
	}
}

void Win32GeometryResource::setStyle(DrawStyle style) {

	if (mp_fillBrush != nullptr && mp_edgeBrush != nullptr) {

		// set colors of brushes
		mp_fillBrush->SetColor(Win32Utils::D2D1Color(style.getFillColor()));
		mp_edgeBrush->SetColor(Win32Utils::D2D1Color(style.getEdgeColor()));
	}

	// delete stroke style
	if (mp_strokeStyle != nullptr) {
		Win32Utils::safeRelease(&mp_strokeStyle);
	}

	// create new Stroke style
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_2DFactory != nullptr) {

		p_2DFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties(
				D2D1_CAP_STYLE_FLAT,
				D2D1_CAP_STYLE_FLAT,
				D2D1_CAP_STYLE_ROUND,
				D2D1_LINE_JOIN_MITER,
				10.0f,
				(D2D1_DASH_STYLE)style.getLineStyle(),
				0.0f
			),
			NULL,
			0,
			&mp_strokeStyle
		);
	}

	// change thickness
	m_style = style;
}
