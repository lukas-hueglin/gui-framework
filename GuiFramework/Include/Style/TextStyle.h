#pragma once
#include "Gui.h"
#include "Style/Color.h"
#include <string>

class TextStyleBuilder;

class GUI_API TextStyle {

private:
	Color m_textColor;
	float m_fontSize;
	std::wstring m_fontName;

private:
	TextStyle();
public:
	~TextStyle();

public:
	static TextStyleBuilder create();

	Color& getTextColor();
	float getFontSize();
	std::wstring getFontName();

	friend class TextStyleBuilder;
};