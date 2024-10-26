#include "Gui.h"
#include "Widgets/Label.h"
#include "Style/Style.h"

Label::Label(Window* p_parent, const wchar_t* text) : Widget(p_parent), m_text(text), m_textAlignment(Alignment::CenterLeft) {

	// create text resource
	mp_textResource = new TextResource(mp_graphics, Style::Normal());
}

Label::~Label() {

	delete mp_textResource;
}

void Label::onPaint() {

	Widget::onPaint();

	// draw text
	mp_textResource->drawText(m_text, m_contentRect, m_textAlignment);
}
