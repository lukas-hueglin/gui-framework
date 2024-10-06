#include "Gui.h"
#include "Widgets/Label.h"
#include "Style/Style.h"

Label::Label(Window<Graphics2D>* p_parent, const wchar_t* text) : Widget(p_parent), m_text(text), m_textAlignment(Alignment::CenterLeft) { }

void Label::onPaint() {

#ifdef DEBUG_UI
	Widget::onPaint();
#endif

	// draw text
	mp_graphics->drawText(m_text, m_contentRect, Style::Normal(), m_textAlignment);
}
