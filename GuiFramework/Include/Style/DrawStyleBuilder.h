#pragma once
#include "Gui.h"
#include "Style/DrawStyle.h"

class GUI_API DrawStyleBuilder {

private:
    DrawStyle m_drawStyle;

public:
    DrawStyleBuilder(DrawStyle& drawStyle);

public:
    DrawStyleBuilder& edgeColor(const Color& edgeColor);
    DrawStyleBuilder& fillColor(const Color& fillColor);

    DrawStyleBuilder& edgeThickness(const float edgeThickness);

    // conversion operator
    operator DrawStyle();
};