#include "Gui.h"
#include "Widgets/Slider.h"
#include "Style/Style.h"
#include <sstream>

// define all types of Sliders to be used
template class Slider<float>;
template class Slider<double>;
template class Slider<int>;

template<typename T>
Slider<T>::Slider(Window* p_parent, T value, T min, T max) :
	TextBox(p_parent, std::to_wstring(value)),
	
	m_value(value), m_min(min), m_max(max),
	
	m_sliderRect(Math::Rect(0.f, 0.f, 0.f, 0.f)) {

	// set requireDoubleClick to true
	m_requireDoubleClk = true;

	// create geometry resources
	mp_sliderResource = new GeometryResource(mp_graphics, Style::Slider());
}

template<typename T>
Slider<T>::~Slider() {

	delete mp_sliderResource;
}

template<typename T>
void Slider<T>::onPaint() {

	// call parent function
	TextBox::onPaint();

	// draw slider
	mp_sliderResource->drawRectangle(m_sliderRect);
}

template<typename T>
void Slider<T>::onResize(Math::Rect availableRect) {
	
	TextBox::onResize(availableRect);

	// calculate new slider rectangle
	float ratio = (m_value - m_min) / (float)(m_max - m_min);

	m_sliderRect = m_hitboxRect;
	m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;
}

template<typename T>
void Slider<T>::onMouseHover(Math::Point2D point) {

	// call parent function
	TextBox::onMouseHover(point);

	if (m_mouseDown && !m_edit) {

		// calculate new value
		float ratio = (point.x() - m_hitboxRect.left()) / m_hitboxRect.getWidth();

		if (std::is_same<T, int>::value) {
			m_value = std::round(m_min + ratio * (m_max - m_min));
		}
		else {
			m_value = m_min + ratio * (m_max - m_min);
		}

		// calculate slider rectangle (because of rounding it isn't done directly)
		ratio = (m_value - m_min) / (float)(m_max - m_min);
		m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;
		
		// update the text
		std::wstringstream wss;
		wss << m_value;
		m_text = wss.str();

		updateText();
		requestRedraw();
	}
}

template<typename T>
bool Slider<T>::filterInput(char key) {

	return key == 0x2D || (0x30 <= key && key <= 0x39) || (key == 0x2E && !std::is_same<T, int>::value);
}


template<typename T>
void Slider<T>::disableEditMode(bool backup) {

	// update m_value
	if (!backup) {
		m_value = std::stof(m_text);
		m_value = max(m_min, min(m_max, m_value));
	}

	// calculate new slider rectangle
	float ratio = (m_value - m_min) / (float)(m_max - m_min);

	m_sliderRect = m_hitboxRect;
	m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;

	// convert m_value to string
	std::wstringstream wss;
	wss << m_value;
	m_text = wss.str();

	// update text
	updateText();

	m_edit = false;
	disableImmediateMode();
	requestRedraw();
}