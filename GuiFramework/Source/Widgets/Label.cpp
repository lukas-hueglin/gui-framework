#include "Gui.h"
#include "Widgets/Label.h"
#include "Style/Style.h"

Label::Label(Window* p_parent, std::wstring text) : Widget(p_parent), m_text(text), m_textAlignment(Alignment::CenterLeft) {

	// create text resource
	mp_textResource = new TextResource(mp_graphics, Style::Normal());
	mp_textResource->setText(m_text);
	mp_textResource->setTextAlignment(m_textAlignment);
}

Label::~Label() {

	delete mp_textResource;
}

void Label::onPaint() {

	Widget::onPaint();

	// draw text
	mp_textResource->drawText();
}

void Label::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	mp_textResource->setRect(m_contentRect);
}
