#pragma once
#include "Widgets/Widget.h"
#include "Core/TextResource.h"

template<typename T>
class GUI_API Slider : public Widget {

private:
	T m_value;
	T m_min;
	T m_max;

	Math::Rect m_sliderRect;
	Alignment m_textAlignment;

	bool m_enterValue;
	wchar_t m_buffer[MAX_STRING_SIZE];

	GeometryResource* mp_backgroundResource;
	GeometryResource* mp_sliderResource;

	TextResource* mp_textResource;


public:
	Slider(Window* p_parent, T value, T min=0, T max=1);
	~Slider();

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onKeyDown(Key key) override;
	void onKeyDown(char key) override;

};