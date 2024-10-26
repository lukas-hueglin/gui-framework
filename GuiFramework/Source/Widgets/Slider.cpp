#include "Gui.h"
#include "Widgets/Slider.h"
#include "Style/Style.h"

// define all types of Sliders to be used
template class Slider<float>;
template class Slider<double>;
template class Slider<int>;

template<typename T>
Slider<T>::Slider(Window* p_parent, T value, T min, T max) :
	Widget(p_parent),
	
	m_value(value), m_min(min), m_max(max),
	m_textAlignment(Alignment::CenterLeft),
	
	m_sliderRect(Math::Rect(0.f, 0.f, 0.f, 0.f)),
	m_enterValue(false) {

	// create geometry and text resources
	mp_backgroundResource = new GeometryResource(mp_graphics, Style::Secondary());
	mp_sliderResource = new GeometryResource(mp_graphics, Style::Accent());
	mp_textResource = new TextResource(mp_graphics, Style::Normal());
}

template<typename T>
Slider<T>::~Slider() {

	delete mp_backgroundResource;
	delete mp_sliderResource;
	delete mp_textResource;
}

template<typename T>
void Slider<T>::onPaint() {

	Widget::onPaint();

	// draw background
	mp_backgroundResource->drawRectangle(m_hitboxRect);

	// draw slider
	mp_sliderResource->drawRectangle(m_sliderRect);

	// draw text
	wchar_t fmt[] = L"%.2f";
	_snwprintf_s(m_buffer, MAX_STRING_SIZE, sizeof(fmt), fmt, m_value);

	mp_textResource->drawText(m_buffer, m_contentRect, m_textAlignment);
}

template<typename T>
void Slider<T>::onResize(Math::Rect availableRect) {
	
	Widget::onResize(availableRect);

	// calculate new slider rectangle
	float ratio = (m_value - m_min) / (float)(m_max - m_min);

	m_sliderRect = m_hitboxRect;
	m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;
}

template<typename T>
void Slider<T>::onMouseHover(Math::Point2D point) {

	if (m_mouseDown) {

		// calculate new value
		float ratio = (point.x() - m_hitboxRect.left()) / m_hitboxRect.getWidth();
		m_value = m_min + ratio * (m_max - m_min);

		// calculate slider rectangle (because of rounding it isn't done directly)
		ratio = (m_value - m_min) / (float)(m_max - m_min);
		m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;
		
		requestRedraw();
	}
}

template<typename T>
void Slider<T>::onMouseDown(bool doubleClk) {

	Widget::onMouseDown(doubleClk);
	
	if (doubleClk) {
		m_enterValue = true;
	}
}

template<typename T>
void Slider<T>::onKeyDown(Key key) {
}

template<typename T>
void Slider<T>::onKeyDown(char key) {
}
