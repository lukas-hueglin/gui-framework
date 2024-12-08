#pragma once
#include "Widgets/Widget.h"
#include "Core/TextResource.h"
#include "Core/GeometryResource.h"
#include "Widgets/PlotSeries.h"

#include <vector>

enum AxisScale {
	Linear = 0,
	Logarithmic = 1
};

enum Unit {
	Second = 0,
	Meter = 1,
	Kilogram = 2,
	Ampere = 3,
	Kelvin = 4,
	Mole = 5,
	Candela = 6,

	Volts = 7,
	Hertz = 8,
	Radians = 9
};

const wchar_t unit_symbols[10] = { L's', L'm', L'g', L'A', L'K', L'mol', L'cd', L'V', L'Hz', L'rad' };
const wchar_t unit_prefixes[8] = { L'n', L'\u00B5', L'm', L' ', L'k', L'M', L'G', L'T' };


class GUI_API Plot : public Widget {

private:

	Math::Rect m_plotRect;
	Math::Rect m_plotBounds;

	std::wstring m_xAxis;
	std::wstring m_yAxis;

	AxisScale m_xAxisScale;
	AxisScale m_yAxisScale;

	Unit m_xAxisUnit;
	Unit m_yAxisUnit;

	float m_xPrescaler;
	float m_yPrescaler;

	std::vector<PlotSeries*> mp_series;

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

	void setXAxisScale(AxisScale scale);
	void setYAxisScale(AxisScale scale);

	void setXUnit(Unit unit);
	void setYUnit(Unit unit);

	void addPlotSeries(PlotSeries* p_plotSeries);

	Math::Point2D plotToScreenSpace(Math::Point2D point);

	Math::Point2D screenToPlotSpace(Math::Point2D point);
	Math::Point2D relativeScreenToPlotSpace(Math::Point2D point);

private:
	float calculateTickStep(float width, int prefDivs, int base, float prefactor);

	void drawHorizontalTicks(float value, std::wstring text);
	void drawVerticalTicks(float value, std::wstring text);

	// make PlotSeries a friend
	friend class PlotSeries;
};
