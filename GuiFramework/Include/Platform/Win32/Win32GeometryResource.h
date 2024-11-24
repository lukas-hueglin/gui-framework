#include "Core/IGeometryResource.h"

class GUI_API Win32GeometryResource : public IGeometryResource {

private:
	ID2D1SolidColorBrush* mp_fillBrush;
	ID2D1SolidColorBrush* mp_edgeBrush;

	ID2D1StrokeStyle* mp_strokeStyle;

public:
	Win32GeometryResource(Graphics2D* p_graphics, DrawStyle style);
	~Win32GeometryResource();

private:
	void initGraphicsAssets();

public:
	void drawLine(Math::Point2D& a, Math::Point2D& b);
	void drawArrow(Math::Point2D& a, Math::Point2D& b, float size);
	void drawRectangle(Math::Rect& rect);

	void setStyle(DrawStyle style);

	// make Win32Graphics2D a friend
	friend class Win32Graphics2D;
};