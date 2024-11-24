#pragma once
#include "Widgets/Widget.h"
#include "Core/TextResource.h"
#include "Core/GeometryResource.h"

class GUI_API Plot : public Widget {

private:

	Math::Rect m_plotRect;
	Math::Rect m_plotBounds;

	std::wstring m_xaxis;
	std::string y_axis;

	GeometryResource* mp_backgroundGeometryResource;
	GeometryResource* mp_axisGeometryResource;
	GeometryResource* mp_linesGeometryResource;
	TextResource* mp_textResource;

	bool m_lockXZoom;
	bool m_lockYZoom;

public:
	Plot(Window* p_parent);
	~Plot();

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseScroll(bool up, bool shift, bool ctr) override;

	void setLockXZoom(bool lock);
	void setLockYZoom(bool lock);

private:
	Math::Point2D plotToScreenSpace(Math::Point2D point);

	Math::Point2D screenToPlotSpace(Math::Point2D point);
	Math::Point2D relativeScreenToPlotSpace(Math::Point2D point);

	void drawHorizontalTicks(float value);
	void drawVerticalTicks(float value);
};
