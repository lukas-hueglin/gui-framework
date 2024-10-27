#include "Gui.h"
#include "Style/TextStyleBuilder.h"
#include "Style/TextStyle.h"
#include <string>

TextStyleBuilder::TextStyleBuilder(TextStyle& textStyle) : m_textStyle(textStyle) { }

TextStyleBuilder& TextStyleBuilder::textColor(const Color& textColor) {

	m_textStyle.m_textColor = textColor;
	return *this;
}

TextStyleBuilder& TextStyleBuilder::fontSize(const float fontSize) {

	m_textStyle.m_fontSize = fontSize;
	return *this;
}

TextStyleBuilder& TextStyleBuilder::fontName(std::wstring fontName) {

	m_textStyle.m_fontName = fontName;
	return *this;
}


TextStyleBuilder::operator TextStyle() {

	return this->m_textStyle;
}
