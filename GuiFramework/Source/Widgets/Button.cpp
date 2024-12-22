#include "Gui.h"
#include "Widgets/Button.h"
#include "Style/Style.h"

Button::Button(Window* p_parent, std::wstring text, WidgetStyle style) : Label(p_parent, text, style), mp_client(nullptr), m_id(0), m_buttonImpl(mp_graphics, style) { }

void Button::onPaint() {

	// draw background by calling the widgetImpl's onPaint
	//m_widgetImpl.onPaint();

	// draw box
	WidgetState state = m_mouseDown ? WidgetState::Click : m_mouseHover ? WidgetState::Hover : WidgetState::Normal;
	m_buttonImpl.onPaint(state);

	// draw text
	m_labelImpl.onPaint(m_text);

	// call master parent function
	Frame::onPaint();
}

void Button::onResize(Math::Rect availableRect) {

	// call parent function
	Label::onResize(availableRect);

	m_buttonImpl.onResize(m_hitboxRect);
}

void Button::onMouseRelease(Math::Point2D point) {

	// call parent first, then call connected function
	Widget::onMouseRelease(point);

	if (mp_client != nullptr) {
		mp_client->onSignalReceived(m_id);
	}
}

void Button::connect(Object* p_client, int id) {

	mp_client = p_client;
	m_id = id;
}
