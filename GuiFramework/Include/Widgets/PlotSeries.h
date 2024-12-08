#pragma once
#include "Style/DrawStyle.h"
#include "Core/GeometryResource.h"

// forward declare Plot
class Plot;

class GUI_API PlotSeries {

protected:
	Plot* mp_parent;
	Graphics2D* mp_graphics;

	GeometryResource* mp_geometryResource;

public:
	PlotSeries(Plot* p_parent);
	~PlotSeries();

public:
	virtual void onPaint(Math::Rect& available) = 0;
	void setStyle(DrawStyle style);

};