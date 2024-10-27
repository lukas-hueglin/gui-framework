#pragma once
#include "Gui.h"
#include "Style/TextStyle.h"

class GUI_API TextStyleBuilder {

private:
    TextStyle m_textStyle;

public:
    TextStyleBuilder(TextStyle& textStyle);

public:
    TextStyleBuilder& textColor(const Color& textColor);

    TextStyleBuilder& fontSize(const float fontSize);
    TextStyleBuilder& fontName(std::wstring fontName);

    // conversion operator
    operator TextStyle();
};