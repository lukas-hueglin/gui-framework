#pragma once
#include "Gui.h"

struct GUI_API RGBColor {
	float r;
	float g;
	float b;
	float a;
};

struct GUI_API HSVColor {
	float h;
	float s;
	float v;
	float a;
};

// create alias for RGBColor
using Color = RGBColor;