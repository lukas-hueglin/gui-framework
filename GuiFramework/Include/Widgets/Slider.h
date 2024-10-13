#pragma once
#include "Widgets/Widget.h"

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

public:
	Slider(Window<Graphics2D>* p_parent, T value, T min=0, T max=1);

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseDown(bool doubleClk) override;
	void onKeyDown(Key key) override;
	void onKeyDown(char key) override;

};