#pragma once
#include "Gui.h"
#include "Style/Color.h"


class TextStyleBuilder;

class GUI_API TextStyle {

private:
	Color m_textColor;
	float m_fontSize;
	const wchar_t* m_fontName;

private:
	TextStyle();
public:
	~TextStyle();

public:
	static TextStyleBuilder create();

	Color& getTextColor();
	float getFontSize();
	const wchar_t* getFontName();

	friend class TextStyleBuilder;
};