#include "Gui.h"
#include "Widgets/PlotSeries.h"
#include "Style/Style.h"
#include "Widgets/Plot.h"

PlotSeries::PlotSeries(Plot* p_parent) : mp_parent(p_parent), mp_graphics(p_parent->mp_graphics) {

	// create geometryResource
	mp_geometryResource = new GeometryResource(mp_graphics, Style::Plot3(0));
}

PlotSeries::~PlotSeries() {

	delete mp_geometryResource;
}

void PlotSeries::setStyle(DrawStyle style) {

	mp_geometryResource->setStyle(style);
}
