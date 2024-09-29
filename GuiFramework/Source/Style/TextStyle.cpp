#include "Gui.h"
#include "Style/TextStyle.h"
#include "Style/TextStyleBuilder.h"

TextStyle::TextStyle() : m_textColor(Color::Black), m_fontSize(12), m_fontName(L"SegoeUI") { }

TextStyle::~TextStyle() {}

TextStyleBuilder TextStyle::create() {

	TextStyle s;
	return TextStyleBuilder(s);
}

Color& TextStyle::getTextColor() {
	return m_textColor;
}

float TextStyle::getFontSize() {
	return m_fontSize;
}

const wchar_t* TextStyle::getFontName() {
	return m_fontName;
}
