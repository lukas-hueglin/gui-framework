#pragma once
#include "Widgets/TextBox.h"
#include "Core/TextResource.h"

template<typename T>
class GUI_API Slider : public TextBox {

private:
	T m_value;
	T m_min;
	T m_max;

	Math::Rect m_sliderRect;

	GeometryResource* mp_sliderResource;


public:
	Slider(Window* p_parent, T value, T min=0, T max=1);
	~Slider();

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseHover(Math::Point2D point) override;

	void setRequireDoubleClk(bool requireDoubleClk) = delete;

private:
	bool filterInput(char key) override;

	void disableEditMode(bool backup);
};