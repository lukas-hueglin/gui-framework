#include "Widgets/PlotSeries.h"

class GUI_API PlotSeries1D : public PlotSeries {

private:
	float* mpa_data;

	float m_lowerBound;
	float m_upperBound;

	int m_size;

public:
	PlotSeries1D(Plot* p_parent, float* pa_data, float lower, float upper, int size);
	~PlotSeries1D();

	void onPaint(Math::Rect& available) override;

	void setBounds(float lower, float upper);
};