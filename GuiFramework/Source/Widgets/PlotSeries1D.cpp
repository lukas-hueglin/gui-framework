#include "Gui.h"
#include "Widgets/PlotSeries1D.h"
#include "Widgets/Plot.h"

#include <vector>

PlotSeries1D::PlotSeries1D(Plot* p_parent, float* pa_data, float lower, float upper, int size) :
	PlotSeries(p_parent), mpa_data(pa_data), m_size(size) {

	// set bounds, that way a x data array is initialized
	setBounds(lower, upper);
}

PlotSeries1D::~PlotSeries1D() {

}

void PlotSeries1D::onPaint(Math::Rect& available) {

	// create Point2D vector
	std::vector<Math::Point2D> points;

	// calculate step
	float step = (m_upperBound - m_lowerBound) / m_size;

	for (int i = 0; i < m_size; ++i) {

		Math::Point2D point = mp_parent->plotToScreenSpace(Math::Point2D(m_lowerBound + step * i, mpa_data[i]));

		points.push_back(point);
	}

	// draw polygon
	mp_geometryResource->setMask(available);
	mp_geometryResource->drawPolygon(&points);
	mp_geometryResource->releaseMask();
}

void PlotSeries1D::setBounds(float lower, float upper) {

	m_lowerBound = lower;
	m_upperBound = upper;
}