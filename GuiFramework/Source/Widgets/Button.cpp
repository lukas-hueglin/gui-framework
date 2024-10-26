#include "Gui.h"
#include "Widgets/Button.h"
#include "Style/Style.h"

Button::Button(Window* p_parent, const wchar_t* text) : Label(p_parent, text), mp_func(nullptr) {

	// create geometry resources
	mp_rectangleResource = new GeometryResource(mp_graphics, Style::Secondary());
}

Button::~Button() {
	
	delete mp_rectangleResource;
}

void Button::onPaint() {

	// draw background
	mp_rectangleResource->setStyle(m_mouseDown ? Style::Highlight() : m_mouseHover ? Style::Accent() : Style::Secondary());
	mp_rectangleResource->drawRectangle(m_hitboxRect);

	// draw text
	Label::onPaint();
}

void Button::onMouseRelease() {

	// call parent first, then call connected function
	Widget::onMouseRelease();

	if (mp_func != nullptr) {
		mp_func();
	}
}

void Button::connect(void(*p_func)()) {

	mp_func = p_func;
}
