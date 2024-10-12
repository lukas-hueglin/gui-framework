#include "Gui.h"
#include "Widgets/Button.h"
#include "Style/Style.h"

Button::Button(Window<Graphics2D>* p_parent, const wchar_t* text) : Label(p_parent, text), mp_func(nullptr) { }

void Button::onPaint() {

	// draw background
	mp_graphics->drawRectangle(m_hitboxRect, m_mouseDown ? Style::Highlight() : m_mouseHover ? Style::Accent() : Style::Secondary());

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
